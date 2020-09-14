%获取分量
x = Sample1(:,1);
y = Sample1(:,2);
z = Sample1(:,3);

%计算平均值和绝对值acc_aver_abs
x_aver = mean(x);
y_aver = mean(y);
z_aver = mean(z);

acc_aver_abs = abs([x_aver,y_aver,z_aver])

%找到活跃轴序号active_axis
max = 0;active_axis = 1;
for k = 1:3;
if max < acc_aver(k)
max = acc_aver(k);
active_axis = active_axis+1;
end
end

%获取关键轴数据并且转换成正数
data = abs(Sample1(:,active_axis));

%滤波数据
data_f = aver9filter(data);

%计算均值
data_f_aver = mean(data_f);
