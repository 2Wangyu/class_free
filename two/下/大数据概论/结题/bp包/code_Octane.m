

%%首先小组会根据数据创建,mat文件将所有的数据放入其中，并在代码中引用 
%引入目标数据，Load
%load data_Octane.mat
load matlab1.mat
%这是一个利用神经网络模型对数据进行训练并预测的代码
%最最重要的是注意数据的行和列 
% 这里要注意，1）我们要将指标变为列向量，
%            2）使用sim函数预测
%如果行和列产生问题，会不断的进行调试
%sim(net, new_X(1,:)')

% 写一个循环，预测接下来题目中要求的样本未知量
psredicty = zeros(30,1); % 初始化predict_y
for j = 1: 30
    %我们需要预测几期的数据就在循环中写j等于几
    %一行行的预测，实际上代表的是对于要预测的每个样本，一个样本一个样本的数据进行预测
    %预测的时候必须是列向量，所以转置的符号是否需要取决于实际情况
    tempresult = sim(net, new_X(j,:)');
    %每一次的数据都用tempresult进行存储，每次计算每次更新
    %将result中的数据写入其中
    psredicty(j) = tempresult;
end
%在终端中展示我的预测数据
fprintf('预测值为：')
%逐个输出
disp(psredicty)



