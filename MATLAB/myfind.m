function [ loc,fillorder ] = myfind( x,aver,thresh)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
n = length(x);
k = 1;
max = 0;
min = 4096;
loc = zeros(40,2);
locmin = 0;
locmin1 = 0;
locmax = 0;
locmax1 = 0;
fillorder = 1;
    %find the first point excceed theresh
    while (abs(x(k)-aver) < thresh) && (k < n);
        k = k +1;
    end
    
    while k < n
        %find the lowest point
         while x(k) < aver;
             if min > x(k)
                  min = x(k);
                  locmin1 = k;
             end
              k = k + 1;
         end
         %record lowest point
         if(locmin1 > locmin)%find new data
             loc(fillorder,1) = min;
             loc(fillorder,2) = locmin1;
             locmin = locmin1;
             fillorder = fillorder + 1;
         end
         %find the highest point
         while(x(k) > aver)
             if max < x(k)
                 max = x(k);
                 locmax1 = k;
             end
             k = k + 1;
         end
         %record the highest point
         if(locmax1 > locmax)
             loc(fillorder,1) = min;
             loc(fillorder,2) = locmin1;
             locmin = locmin1;
             fillorder = fillorder + 1;
         end
    end
   
       
          
          
  
    
    
       

