%��ȡ����
x = Sample1(:,1);
y = Sample1(:,2);
z = Sample1(:,3);

%����ƽ��ֵ�;���ֵacc_aver_abs
x_aver = mean(x);
y_aver = mean(y);
z_aver = mean(z);

acc_aver_abs = abs([x_aver,y_aver,z_aver])

%�ҵ���Ծ�����active_axis
max = 0;active_axis = 1;
for k = 1:3;
if max < acc_aver(k)
max = acc_aver(k);
active_axis = active_axis+1;
end
end

%��ȡ�ؼ������ݲ���ת��������
data = abs(Sample1(:,active_axis));

%�˲�����
data_f = aver9filter(data);

%�����ֵ
data_f_aver = mean(data_f);
