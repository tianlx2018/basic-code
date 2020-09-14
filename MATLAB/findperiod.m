function [ len,sum ] = findperiod( x,start,aver )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
k = start;
sum = 0;
n = length(x);
if x(k) < aver;
   while ((x(k) < aver) && ( k < n));
       sum = sum + x(k)-aver;
       k = k + 1;
   end
else
   while (x(k) > aver) && ( k < n);
       sum = sum + x(k)-aver;
       k = k + 1;
   end    
end
len = k - start;
end

