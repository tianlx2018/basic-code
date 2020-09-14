function [ y] = noisefilter( x,thresh)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
n  = length(x);
y = zeros(n,1);
x_mean = mean(x);
for k = 1:n  
    if abs(x(k) - x_mean) < thresh
        y(k) = x_mean;
    else
        y(k) = x(k);
    end
end

