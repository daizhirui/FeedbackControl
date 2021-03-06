k = 1;                                     
numH = 1;                               % form numerator
denH = [1 k];                            % form denominator
sysH = tf(numH,denH);             % define system by its numerator and denominator
w = logspace(-2,2);                   % set frequency w to 50 values from 10^-2 to 10^2
[mag, phase] = bode(sysH,w);    % compute frequency response
figure(1)
loglog(w,squeeze(mag));             % log-log plot of amplitude
hold on;
figure(2)
semilogx(w,squeeze(phase));       % semi log plot of phase
hold on;
figure(3)
step(sysH);
