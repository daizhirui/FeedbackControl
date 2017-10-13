k = 1;      % form numerator
numH = 1;
denH = [1 k];
sysH = tf(numH,denH);
w = logspace(-2,2);
[mag, phase] = bode(sysH,w);
loglog(w,squeeze(mag));
semilogx(w,squeeze(phase));