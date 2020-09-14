function [  ] = pross2( data )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
x = data(:,1);
y = data(:,2);
z = data(:,3);
n = 1: length(x);
acc = sqrt(x.^2+y.^2+z.^2);

acc_f = aver9filter(acc);

acc_m = mean(acc_f);

plot(n,acc_f,n,acc_m);

end

