clc
clear
close all;
load('data1.mat') %读入附件2处理的
%%%load('data1.mat') %读入附件1处理的
%%%%% 两个问题本质上代码是一样，只是修改参数

rmse_record = [];
W_record = [];
weilai = [];
for c=1:size(appendix2,2) 
    data = appendix2{1,c}; %我们对不同的分拣中心用data来存
    for i=1:size(data,1)
        if data(i,4)==0
            data(i,4)=0.1;
        end
    end
%     %%
%         data = appendix1{1,c}; 
%     train_num = 5; 
%     %%
    train_num = 100; 
    %1.1问题需要修改参考期数为4 train_num = 4;
    
    %% 下面是ARIMA计算权重
    [y_train_ARIMA]=ARIMA(data(1:end-train_num,4),train_num); 
    y_ture_ARIMA = data(end-train_num+1:end,4);
    % 下面计算RMSE
    RMSE_ARIMA = sqrt(mean((y_train_ARIMA - y_ture_ARIMA).^2));
    %% 下面是LSTM计算权重
    ref = 120; %参考历史的多少期
    %%%%% ref = 30;
    [y_train_LSTM]=LSTM(data(1:end-train_num,4),ref,train_num);
    y_ture_LSTM = data(end-train_num+1:end,4);
    % 下面计算RMSE
    RMSE_LSTM = sqrt(mean((y_train_LSTM - y_ture_LSTM).^2));
    %% 下面计算权重
    W_ARIMA = (1/RMSE_ARIMA)/((1/RMSE_ARIMA)+(1/RMSE_LSTM));
    W_LSTM = 1-W_ARIMA;
    quanzhongle(c,1) = data(1,1); %记录id
    quanzhongle(c,2) = W_ARIMA; %记录ARIMA的RMSE
    quanzhongle(c,3) = W_LSTM; %记录LSTM的RMSE
    %% 下面正式预测
    total_step = 720;
    pre_step = total_step/3; %预测未来多少期的值
    %%pre_step = 30;
    
    % ARIMA
    [pre_ARIMA]=ARIMA(data(:,4),pre_step); 
    % LSTM
    [pre_LSTM]=LSTM(data(:,4),ref,pre_step);
    % 混合
    pre = pre_ARIMA*W_ARIMA + pre_LSTM*W_LSTM;
    pre = [pre;pre;pre];
    weilai(1,c) = data(1,1); %记录id
    weilai(2:1+total_step,c) = pre; %记录预测值
    %% 计算RMSE
    RMSE_ARIMA = sqrt(mean((pre_ARIMA - data(end-pre_step+1:end,4)).^2));
    RMSE_LSTM = sqrt(mean((pre_LSTM - data(end-pre_step+1:end,4)).^2));
    rmser(c,1) = data(1,1); %记录id
    rmser(c,2) = RMSE_ARIMA; %记录ARIMA的RMSE
    rmser(c,3) = RMSE_LSTM; %记录LSTM的RMSE
end

%% 绘制RMSE的图表
figure;
subplot(2,1,1);
plot(rmser(:,1), rmser(:,2), 'r-', 'LineWidth', 2);
hold on;
plot(rmser(:,1), rmser(:,3), 'b-', 'LineWidth', 2);
xlabel('分拣中心');
ylabel('RMSE');
legend('ARIMA', 'LSTM');
title('RMSE对比');
grid on;

%% 绘制权重的图表
subplot(2,1,2);
plot(quanzhongle(:,1), quanzhongle(:,2), 'r-', 'LineWidth', 2);
hold on;
plot(quanzhongle(:,1), quanzhongle(:,3), 'b-', 'LineWidth', 2);
xlabel('分拣中心');
ylabel('权重');
legend('ARIMA', 'LSTM');
title('权重对比');
grid on;
