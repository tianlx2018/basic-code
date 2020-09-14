function [ pos,neg] = Energy( x)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
% n = length(x);
% s = sum(x);
% m = 0;
% for k = 1:n;
%    m = m + (x(k)/s)^2;
% end
% Engery = m/n;
 n = length(x);
 pos = 0;
 pnum = 0;
 neg = 0;
 nnum = 0;
 for k = 1:n;
     if x(k)>0
         pos = pos + x(k);
         pnum = pnum+1;
     else
         neg = neg + x(k);
         nnum = nnum+ 1;
     end
 end
pos = pos/pnum;
neg = neg/nnum;

