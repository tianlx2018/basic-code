function [  ] = preprocss( data)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
% get length
n = length(data);
time = 1:n;

x = data(:,1);
y = data(:,2);
z = data(:,3);

% plot original data dc
figure;
subplot(3,1,1);
plot(time,x,'b');
title('X Y Z original data dc');
legend('X-axis');
grid;

subplot(3,1,2);
plot(time,y,'r');
legend('Y-axis');
grid;

subplot(3,1,3);
plot(time,z,'g');
legend('Z-axis');
grid;

% plot original data ac
x_ac = x - mean(x);
y_ac = y - mean(y);
z_ac = z - mean(z);

figure;
subplot(3,1,1);
plot(time,x_ac,'b');
legend('X-axis');
title('X Y Z original data ac');
grid;

subplot(3,1,2);
plot(time,y_ac,'r');
legend('Y-axis');
grid;

subplot(3,1,3);
plot(time,z_ac,'g');
legend('Z-axis');
grid;

% 10 point filter

x_f = aver9filter(x_ac);
y_f = aver9filter(y_ac);
z_f = aver9filter(z_ac);

% display data
figure;
subplot(3,1,1);
plot(time,x_f,'b');
legend('X-axis');
title('X Y Z data ac  passed filter');
grid;

subplot(3,1,2);
plot(time,y_f,'r');
legend('Y-axis');
grid;

subplot(3,1,3);
plot(time,z_f,'g');
legend('Z-axis');
grid;

end

