clear all

close all


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% If these are changed, optimization needs to be regenerated and compiled.

T = 20; 
L = 10;

% T = 5; 
% L = 3; 


S = 5;
% S = 5;

saveIter=-1;
% saveIter=0;

error_norm='l2';
% error_norm='l1';
% input_norm='energy';
input_norm='l2';


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Receding horizon
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
s = RandStream('mt19937ar','Seed',1);
RandStream.setGlobalStream(s);
% figure(1),clf

% process parameters
simulation.Vsupply=6;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Choose which model to use
% with one inductor from Amazon, can go up to about Ts=19ms
simulation.RM=2.62;        % Ohm
simulation.LM=.0259;       % H
simulation.Kb=.01;  
simulation.KM=.01;
simulation.JM=3.75e-6;
simulation.bM=1.3e-5;

simulation.A=[-simulation.RM/simulation.LM,-simulation.Kb/simulation.LM,0;
              simulation.KM/simulation.JM,-simulation.bM/simulation.JM,0;
              0,1,0];
simulation.B=[1/simulation.LM;
              0;
              0];
simulation.BB=[0;
               1;
               0];
simulation.C=[0 0 1];        % only measure angle  


[nx,nu] = size(simulation.B);
nd = size(simulation.BB,2);
nd = size(simulation.B,2);
ny = size(simulation.C,1);

B = [simulation.B,simulation.BB]; % concatentate B matrix for discretized model

%% Discretized model (Euler discretization):
% sampling time
% Ts=.001; % 1 ms
Ts=.005; % 5 ms
% Ts=.008; % 8 ms
% Ts=.010; % 10 ms
% Ts=.012; % 12 ms
% Ts=.015; % 15 ms
% Ts=.018; % 18 ms
% Ts=.020; % 20 ms


if 0 % Euler discretization
    Ad=eye(nx)+Ts*simulation.A;
    Bd=Ts*B;
    Cd=simulation.C;
    SYSD=ss(Ad,Bd,Cd,0,Ts);
else % zoh
    SYSD=c2d(ss(simulation.A,B,simulation.C,0),Ts);
end




if 0
    !rm -f *toremove* tmpC*.c tmpC*.mex* tmpC*.h @tmp*/*.? @tmp*/*.log;
    [classname]=generateOptimizationMPCMHE(SYSD,T,L,S,error_norm,input_norm);
else
    classname = 'tmpC_TS_20161011_155522_861392_classname';
% else 
%     disp('Previously unused horizon lengths. Generating new code.')
%     [classname,sys]=generateOptimizationMPCMHE(T,L,S,error_norm,input_norm);
end


obj=feval(classname);
load(obj,0);
load(obj,1);

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%% simulation parameters
dSigma=0;%.001;
nSigma=0;%.05;
uMax=simulation.Vsupply;


%% optimization parameters

simulation.refWeight=10;
simulation.uWeight=1;%1e-5;
if strcmp(error_norm,'l2')
    simulation.uWeight=2; %1e-5;
%     simulation.uWeight=1e-6; %1e-5;
    % Use smaller weight with smaller Ts.
end
simulation.nWeight=1e6;%1e12;
simulation.dWeight=5;

%% Set parameters
setP_Vsupply(obj,simulation.Vsupply);

setP_RM(obj,simulation.RM);
setP_inv_LM(obj,1/simulation.LM);
setP_Kb(obj,simulation.Kb);
setP_KM(obj,simulation.KM);
setP_inv_JM(obj,1/simulation.JM);
setP_bM(obj,simulation.bM);

% setP_a(obj,a);
% setP_b(obj,b);

setP_refWeight(obj,simulation.refWeight);
setP_uWeight(obj,simulation.uWeight);
setP_dWeight(obj,simulation.dWeight);
setP_nWeight(obj,simulation.nWeight);


%% 
Tfinal=10;

nPoints=16*floor(Tfinal/Ts/16);

nPoints=nPoints/2;
% nPoints=5;

% Initialize vectors of stored data
uFull=zeros(nu,nPoints);
dFull=zeros(nd,nPoints);
uPastFull=zeros(L,nPoints);
uApplyFull=zeros(S,nPoints);
optUFull=zeros(T,nPoints);
optDFull=zeros(L+T,nPoints);
optXFull=zeros(nx*(L+T),nPoints);
optX0Full=zeros(nx,nPoints);
yPastFull=zeros(L+1,nPoints);
optNoiseFull=zeros(L+1,nPoints);
optJFull=zeros(1,nPoints);
optEnergyFull=zeros(1,nPoints);
refFull=zeros(T,nPoints);
xtFull=zeros(nx,nPoints);
xtEstFull=zeros(nx,nPoints);
yFull=zeros(ny,nPoints);
yActualFull=zeros(ny,nPoints);
nFull=zeros(ny,nPoints);
time=zeros(1,nPoints);

% Tolerance to step back from saturation
tol=.9;

%% reference function

if 0   % sinusoidal reference for theta
    omegaRef=3.2*pi;  
    simulation.Ref=@(t)2*pi*sin(omegaRef*t);
elseif 1 % square wave reference for theta
%     omegaRef=2*pi;
    omegaRef=pi;
%     simulation.Ref=@(t)2*pi*sign(sin(omegaRef*t));
    simulation.Ref=@(t)2*pi*sign(sin(omegaRef*t));
%     simulation.Ref=@(t)pi/2*ones(length(t),1);
else   % constant reference for theta
    simulation.Ref=@(t)10*ones(size(t));
end


% Check Euler discretization
Ad=eye(nx)+Ts*simulation.A;
if any(abs(eig(Ad))>1)
    Ad
    eig(Ad)
    error('Euler discretization is unstable, perhaps because of poor conditoning\n');
end


%% Receding Horizon
for k=1:nPoints
    % x= [iM;omega;theta]

%% initialize past data ===================================================

    if k==1
        
        t=Ts*(-L:T)';
        ref=simulation.Ref(t(L+2:end))';
        
        % first time  - generate past data
        thisUpast=zeros(nu,L);
        thisUapply=zeros(nu,S);
        thisDpast=dSigma*randn(nd,L);
        thisNpast=nSigma*randn(ny,L+1);
        
        thisX0=0*randn(nx,1);        
        thisX(:,1)=SYSD.a*thisX0+SYSD.b*[thisUpast(:,1);thisDpast(:,1)];
%         thisX(:,1)=(eye(nx)+Ts*simulation.A)*thisX0+Ts*simulation.B*(thisUpast(:,1)+thisDpast(:,1));
%         thisX(:,1)=(eye(nx)+Ts*simulation.A)*thisX0+Ts*simulation.B*thisUpast(:,1);
        for j=1:L
            thisX(:,j+1)=SYSD.a*thisX(:,j)+SYSD.b*[thisUpast(:,j);thisDpast(:,j)];
%             thisX(:,j+1)=(eye(nx)+Ts*simulation.A)*thisX(:,j)+Ts*simulation.B*(thisUpast(:,j)+thisDpast(:,j));
%             thisX(:,j+1)=(eye(nx)+Ts*simulation.A)*thisX(:,j)+Ts*simulation.B*thisUpast(:,j);
        end
        thisXt=thisX(:,end);
        thisXtActual=thisXt;
        
        thisYpast=SYSD.c*thisX+thisNpast;
%         thisYpast=simulation.C*thisX+thisNpast;
%         thisYpast=simulation.C*thisX;
        thisYpastActual=thisYpast;
        
    else
        
        t=t+Ts;
        ref=simulation.Ref(t(L+2:end))';
        
        % subsequent times - run model
        thisDpast=[thisDpast(:,2:end),dSigma*randn(nd,1)];
        thisNpast=[thisNpast(:,2:end),nSigma*randn(ny,1);];
        thisUpast=[thisUpast(:,2:end),thisUapply(1)];
        thisUapply=optU(2:S+1);
        
        % this goes crazy:
%         thisXt=(eye(nx)+Ts*simulation.A)*thisXt+Ts*simulation.B*(thisUapply(:,end)+thisDpast(:,end));
        
%
        thisXt=SYSD.a*thisXt+SYSD.b*[thisUpast(:,end);thisDpast(:,end)];
%         thisXt=(eye(nx)+Ts*simulation.A)*thisXt+Ts*simulation.B*(thisUpast(:,end)+thisDpast(:,end));
%         thisXt=(eye(nx)+Ts*simulation.A)*thisXt+Ts*simulation.B*thisUpast(:,end);
        
        thisYpast=[thisYpast(:,2:end),SYSD.c*thisXt+thisNpast(:,end)];
%         thisYpast=[thisYpast(:,2:end),simulation.C*thisXt+thisNpast(:,end)];
%         thisYpast=[thisYpast(:,2:end),simulation.C*thisXt];
        
        thisXtActual=SYSD.a*thisXtActual+SYSD.b*[(abs(thisUpast(:,end))>0.72).*thisUpast(:,end);thisDpast(:,end)];
%         thisXtActual=(eye(nx)+Ts*simulation.A)*thisXtActual+Ts*simulation.B*(abs(thisUpast(:,end))>0.72).*thisUpast(:,end)+Ts*simulation.B*thisDpast(:,end);
        
        thisYpastActual=[thisYpastActual(:,2:end),SYSD.c*thisXtActual+thisNpast(:,end)];
%         thisYpastActual=[thisYpastActual(:,2:end),simulation.C*thisXtActual+thisNpast(:,end)];
%         thisYpastActual=[thisYpastActual(:,2:end),simulation.C*thisXtActual];
        
    end
    
    
    %% solver initial conditions ==========================================
    if k == 1
        % cold start
        % Avoid initializing with zero since this alters the sparsity structure
        initU=0*rand(nu,T);
        initD=0*rand(nd,L+T);
        x0=0*rand(nx,1);
        initX=0*rand(nx,L+T);

    else
        if 0 % warm start
            initU=zeros(nu,T-1); % may want to initialize this differently!!!
%             initD=.00001*rand(nd,L+T-1);
            %             x0=simulation.A*optX(:,1)+simulation.B*thisUpast(:,1); % optimal u, zero d
            initX0=optX0;
            initX=optX;
%             x0 = thisX(:,1); % cheating
%             initX(:,1:L) = thisX(:,2:end); % cheating but similar to what we do in C without generating the true states ourselves.
%             for j=L+1:L+T-1
%             initX(:,j) = simulation.A*initX(:,j-1); 
%             end
        else % cold start
            initU=0*rand(nu,T);
            initD=0*rand(nd,L+T);
            x0=0*rand(nx,1);
            initX=0*rand(nx,L+T);
        end
        
        % move away from constraints
        initU=max(min(initU,tol*uMax),-tol*uMax);

    end
        
    
    t0=clock();
    
    % Set parameters
    setP_upast(obj,thisUpast);
    setP_uapply(obj,thisUapply);
    setP_ypast(obj,thisYpastActual);
    setP_ref(obj,ref);
%     setP_t(obj,t);
    % Initialize primal variables
    setV_x0(obj,x0);
    setV_x(obj,initX);
    setV_u(obj,initU);
    setV_d(obj,initD);
    
    if strcmp(error_norm,'l1')
        setV_absError(obj,abs(initX(3,L+1:end)-ref)/tol);
    end
    
    % Solve optimization
    mu0=10;
    maxIter=30;%100;
    [simulation.status(k),...
        simulation.iter(k),...
        simulation.time(k)]=solve(obj,mu0,int32(maxIter),int32(saveIter));
    
    % retrieve outputs
%     [optJ,...
%         optU,optD,...
%         optX,optX0,...
%         optIM,optOmega,optTheta,...
%         optEnergy,optNoise]=getOutputs(obj);
    [optJ,...
        optU,optD,...
        optX,optX0,...
        optIM,optOmega,optTheta,...
        optEnergy,optNoise]=getOutputs(obj);

    dt=etime(clock(),t0);
    
    

    
    %% Force switch
    u=optU;
     
%     switchTol = .7;%.99;
%     if 1
%         for i = 1:length(u)
%             if u(i)>switchTol*uMax
%                 u(i)=uMax;
%             elseif u(i)<-switchTol*uMax
%                 u(i)=-uMax;
%             else
%                 u(i)=0;
%             end
%         end
%     end


    
    
    %% Store data
    uFull(k)=u(1);
    uPastFull(:,k)=thisUpast;
    uApplyFull(:,k)=thisUapply;
    dFull(k)=thisDpast(end);
    optUFull(:,k)=optU;
    optDFull(:,k)=optD;
    optXFull(:,k)=optX(:);
    optX0Full(:,k)=optX0;
    yPastFull(:,k)=thisYpast;
    optNoiseFull(:,k)=optNoise;
    optJFull(:,k)=optJ;
    optEnergyFull(:,k)=optEnergy;
    refFull(:,k)=ref;
    xtFull(:,k)=thisXt;
    xtEstFull(:,k)=optX(:,L+1);
    yFull(:,k)=thisYpast(:,end);
    yActualFull(:,k)=thisYpastActual(:,end);
    nFull(:,k)=thisNpast(:,end);
    time(k)=t(L+1);
    
    
    %% Plot figures
%     figure(1);
%     plot(...
%         time(k),simulation.Ref(time(k)),'r+',...
%         time(k),uFull(1,k),'b*',...
%         time(k),xtFull(1,k),'g.-',...
%         time(k),xtFull(2,k)/10,'k.-',...
%         time(k),xtFull(3,k),'m.-');
% %     ax=axis;
% %     axis([ax(1:2),-1.2*uMax,1.2*uMax]);
%     grid on
%     %      legend('ref_{past}','ref_{future}','u_{future}','u','iM','\omega/10','\theta')
%     legend('ref','u','iM','\omega/10','\theta')
%     xlabel('t [s]')
%     
%     title(sprintf('t=%.4f J=%.2f en=%.2f (st=%d, niter=%d, %.1fus)\n',...
%         time(k),optJ,optEnergy,simulation.status(k),...
%         simulation.iter(k),1e6*simulation.time(k)));
%     hold on
%     drawnow;
    
    
    
end


% figure(1),clf
% plot(...
%     time(L+1:end),simulation.Ref(time(L+1:end)),'r+-',...
%     time,uFull,'b*',...
%     time,yFull,'g.-',...
%     time,yActualFull,'k.-');
% ax=axis;
% axis([ax(1:2),-1.2*uMax,1.2*uMax]);
% grid on
% legend('ref','u','y no dead zone','actual y')
% xlabel('t [s]')

figure(1),clf
plot(...
    time(L+1:end),simulation.Ref(time(L+1:end)),'r+-',...
    time,uFull,'b*',...
    time,100*optDFull(L+1,:),'go',...
    time,yActualFull,'k.-');
ax=axis;
axis([ax(1:2),-1.2*uMax,1.2*uMax]);
grid on
legend('ref','u','100*optD','y')
xlabel('t [s]')

figure(2), clf
plot(...
    time(L+1:end),simulation.Ref(time(L+1:end)),'r+',...
    time,uFull,'b*',...
    time,xtFull(1,:),'g.',...
    time,xtFull(2,:)/10,'k.',...
    time,xtFull(3,:),'m.');
ax=axis;
axis([ax(1:2),-1.2*uMax,1.2*uMax]);
grid on
legend('ref','u','iM','\omega/10','\theta')
xlabel('t [s]')

figure(3), clf
plot(...
    time,simulation.Ref(time),'r-',...
    time,uFull,'b*',...
    time,xtFull(1,:),'g.-',...
    time,xtFull(2,:)/10,'k.-',...
    time,xtFull(3,:),'m.-');
ax=axis;
axis([ax(1:2),-1.2*uMax,1.2*uMax]);
grid on
legend('ref','u','iM','\omega/10','\theta')
xlabel('t [s]')

title(sprintf('t=%.4f J=%.2f en=%.2f (st=%d, niter=%d, %.1fus)\n',...
    time(k),optJ,optEnergy,simulation.status(k),...
    simulation.iter(k),1e6*simulation.time(k)));

% drawnow;



% figure(4),clf
% 
% plot(...
%     time,simulation.Ref(time),'r-',...
%     time,xtFull(1,:),'g.-',...
%     time,xtFull(2,:)/10,'k.-',...
%     time,xtFull(3,:),'m.-',...
%     time,uFull(1,1:k),'b.',...
%     time(simulation.status<0),uFull(1,simulation.status<0),'kx'...
%     );
% ax=axis;
% grid on
% legend('ref','iM','\omega/10','\theta','u','u_{err}')
% 
% title(sprintf('Average energy = %.3f, Average L2 error = %.5f, Average Linf error = %.4f, # failed opt. = %d/%d, mean nIter = %.1f, mean time = %.1f us\n',...
%               (xtFull(1,:)*uFull')/k,...
%               norm(xtFull(3,:)-simulation.Ref(time),2)/k,...
%               mean(abs(xtFull(3,:)-simulation.Ref(time))),...
%               sum(simulation.status(1:k)~=0),k,...
%               mean(simulation.iter(1:k)),...
%               1e6*mean(simulation.time(1:k))...
%               ));


          
simulation_status=simulation.status
iterations_that_did_not_converge=find(simulation.status==-1)
