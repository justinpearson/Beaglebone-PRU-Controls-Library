See Derek Molloy's book 'exploring beaglebone' (:~/exploringBB/chp13/PRUClock)

Um, I think this file is unfinished.

I think the idea was for the CPU to write the desired duty cycle &
direction into some part of the PRU data ram, and the PRU then reads
it and starts generating a PWM signal with the desired duty cycle and
direction. I think we abandoned this because it seemed better to have
the PRU simply use the built-in PWM peripheral. That leaves the PRU
free to do other things, although we lose a little control, e.g., it's
bad if the PWM peripheral is laggy.

-Justin
