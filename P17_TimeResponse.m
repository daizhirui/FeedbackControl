num = 1/1000;
den = [1 50/1000];
sys = tf(num*500, den); % tf Construct transfer function or convert to transfer function.
step(sys);