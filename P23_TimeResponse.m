t = 0:0.02:10;
num = 1;
den = [1 0 9.81];
sys = tf(num, den);
y = step(sys,t);
plot(t,57.3*y)