function [classname]=generateOptimizationMPCMHE(SYSD,T,L,S,error_norm,input_norm)
% classname=generateOptimization(T,L)
%
% Generate class to do estimation and system model, with:
%   T          - length of MPC forward horizon
%  
%   L          - length of MHE backward horizon
%
%   S          - number of inputs to apply while computing
%
%   error_norm - metric used to penalize the tracking error 
%                (l1 or l2)
%   input_norm - metric used to penalize the input signal
%                (l2 or energy)

if nargin<6
    error('Not enough input arguments');
end

%% Match input parameters with the appropriate class
classname='';

% optimizeCS=@class2equilibriumLatentCS;classname='tmpM';% matlab
optimizeCS=@cmex2equilibriumLatentCS;classname='tmpC';  % c
                                               
%codeType='C+asmLB';                                               
%compilerOptimization='-O1';

codeType='C';
% compilerOptimization='-Ofast';
compilerOptimization='-O0';
allowSave=true;

% classname=sprintf('%s_T%d_L%d',classname,T,L); % This is too long! Errors because matlab truncates the name, and then they match already defined names!!!
classname=sprintf(classname);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% System parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Tvariable Vsupply   []; % H-bridge supply voltage
% Tvariable Vswitches []; % H-bridge voltage drop across on switches (total)
% Tvariable Vdiodes   []; % H-bridge voltage drop across flyback diodes (total)

Tvariable RM [1,1]; % DC motor resistance
Tvariable inv_LM [1,1]; % inverse of DC-motor armature inductance
Tvariable Kb [1,1]; % DC motor counter EMF coefficient
Tvariable KM [1,1]; % DC-motor torque constant
Tvariable inv_JM [1,1]; % inverse of DC-motor rotor inertia
Tvariable bM [1,1]; % DC-motor rotor damping

% Variables defining dead zone function
% Tvariable a [1,1]; % nominally 1/2 the width of the dead zone
% Tvariable b [1,1]; % Choose how smooth the discontinuity is (smaller b --> smoother)

%% LTI model

% x= [iM;omega;theta]

% dot x = A*x + B*(u+d)
% y = C*x + n

% A=[-RM*inv_LM,-Kb*inv_LM,0;
%    KM*inv_JM,-bM*inv_JM,0;
%    0,1,0];
% B=[inv_LM;
%    Tzeros([2,1])];
% C=[0 0 1]; % measure theta only



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Setup optimization
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% optimization weights
Tvariable refWeight [];
Tvariable uWeight [];
Tvariable nWeight [];
Tvariable dWeight [];

% time series
% Tvariable t      [L+T+1];      % include t0
Tvariable x0     [3,1];    % value of x(t0)
Tvariable x      [3,L+T];  % values of x(t(2:end))
Tvariable ref    [1,T];  % values of ref(t(L+2:end))
Tvariable u      [1,T];  % values of u(t) 
Tvariable d      [1,L+T];  % values of d(t)
Tvariable upast  [1,L];    % past applied control inputs
Tvariable uapply [1,S];    % inputs to be applied
Tvariable ypast  [1,L+1]; % past sequence of output measurements
verboseLevel=1;


%% Nonlinear state space: nlss(f,g,discrete-time,stateName)
% % uall = [upast,u]+d;
% uall = [upast,u];
% sys=nlss(@(x,uall,t)A*x+B*uall,...
%          @(x,uall,t)C*x,...
%          false,'x');
%      
% [y,x,xDynamics]=sim(sys,uall,t,x0);
%%%%%%%%%%%%%%%%%%%%%
% setInitialState(sys,x0,t(1));
%      
% nT=size(t,1);
%      
% x=Tvariable(sys.stateName,[size(sys.x0,1),nT-1]);
% xpre=[sys.x0,x(:,1:end-1)];
% tpre=t(1:end-1);
% % upre=[upast,u(:,1:end-1)];
% upre=uall(:,1:end-1);
% dx=sys.f(xpre,upre,tpre);
% constraint=(x==xpre+tprod(t(2:end)-tpre,[2],dx,[1,2]));
% xall=[sys.x0,x];
% if strcmp(class(sys.g),'function_handle')
%    y=sys.g(xall,uall,t);
% end
% %%%%%%%%%%%%%%%%%%%%%
% xDynamics=constraint;     
% [xDynamics,y,z]=TltiConstraints(A,B,C,D,G,H,x0,x,[upast,u],L+1,L+T);
% [xDynamics,y,z]=TltiConstraints(A,B,C,0,C,0,x0,x,uall,L+1,L+T);
uall=[upast,u];



A=SYSD.a;
B=SYSD.b;
C=SYSD.c;

xDynamics=(x==A*[x0,x(:,1:L+T-1)]+B*[uall;d]);
y=C*[x0,x(:,1:L+1-1)];
z=eye(size(A))*[x0,x(:,1:L+T)];
% y=C*x(:,1:L+1);
noise=ypast-y;


iM=z(1,:);
omega=z(2,:);
theta=z(3,:);


energy=tprod(u,[-1,-2],iM(:,L+1:end-1),[-1,-2]);

switch (error_norm)
    case 'l2'
        % norm2 of error
        if 1 % angle theta tracks reference
            J=refWeight*norm2(theta(:,L+2:end)-ref);
        else % angular velocity omega tracks reference
            J=refWeight*norm2(omega(:,L+2:end)-ref);
        end
    case 'l1'
        if 1  % angle theta tracks reference
            J=refWeight*sum(abs(theta(:,L+2:end)-ref),2);
        else  % angular velocity omega tracks reference
            J=refWeight*sum(abs(omega(:,L+2:end)-ref),2);
        end
    otherwise
        error('Unknown error_norm "%s"\n',error_norm)
end


switch (input_norm)
  case 'l2'
    % norm2 of voltage
    J=J+uWeight*norm2(u);
  case 'energy'
    J=J+uWeight*energy;
  otherwise
    error('Unknown input_norm "%s"\n',input_norm)
end

% subtract norm of disturbance and noise
J = J - dWeight*norm2(d) - nWeight*norm2(noise);
% J = J - nWeight*norm2(noise);
% J = J - dWeight*norm2(d);



classname=optimizeCS(...
    'pedigreeClass',classname,...
    'method','primalDual',...
    'P1objective',J,...
    'P2objective',-J,...
    'P1optimizationVariables',{u},...
    'P2optimizationVariables',{x0,d},...
    'latentVariables',{x},...
    'P1constraints',{u<=Vsupply,...
                     u>=-Vsupply,...
                     u(1,1:S)==uapply},...
    'P2constraints',{d<=.003,...
                     d>=-.003},...
    'latentConstraints',{xDynamics},...    
    'outputExpressions',{
        J;
        u;
        d;
        x;
        x0;
        iM;omega;theta;
        energy;noise},...
    'parameters',{
            Vsupply;
            RM;inv_LM;Kb;KM;bM;inv_JM;
            refWeight;uWeight;dWeight;nWeight;
            upast;uapply;ypast;
            ref},...
    'muFactorConservative',.9,...
    'gradTolerance',1e-3*10,...
    'equalTolerance',1e-4*10,...
    'desiredDualityGap',1e-3*10,...
    'skipAffine',false,...
    'debugConvergence',true,...
    'debugConvergenceThreshold',1e1,...
    'profiling',false,...
    'codeType',codeType,...
    'addEye2Hessian',1e-6,...
    'scratchbookType','double',...
    'compilerOptimization',compilerOptimization,...
    'allowSave',allowSave,...
    'verboseLevel',verboseLevel);
%profile viewer

% 
% 'parameters',{
%         Vsupply;Vswitches;Vdiodes;RM_by_LM;inv_LM;   
%         refWeight;uWeight;nWeight;dWeight;    
%         upast;ypast;
%         ref;t
%                     },...

% 'P2constraints',{},...
% 'parameters',{DCparameters{:},Weights{:},measurements{:}},...

% Add this line to 'compilerOptimization' to generate standalone server code:
% 'callType','client-server','serverProgramName','tmpC_DCmotor_server','serverAddress','tamina.ece.ucsb.edu','port',1968,...

if isempty(strfind(path,'./outputs:'))
    addpath('./outputs');
end

classname=getValue(classname);
