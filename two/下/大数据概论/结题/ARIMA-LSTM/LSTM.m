function [T_sim]=LSTM(data,ref,step)
data1=data;

%% 3.数据处理
nn=size(data,1);%训练数据集大小
numTimeStepsTrain = floor(nn);%nn数据训练 ，N-nn个用来验证
[XTrain,YTrain,mu,sig,dataPredictStandardized] = shujuchuli(data,numTimeStepsTrain,ref,step);
%% 4.定义LSTM结构参数
numFeatures= ref;%输入节点
numResponses = step;%输出节点
numHiddenUnits = 500;%隐含层神经元节点数 
 
%构建 LSTM网络 
layers = [sequenceInputLayer(numFeatures) 
 lstmLayer(numHiddenUnits) %lstm函数 
dropoutLayer(0.2)%丢弃层概率 
 reluLayer('name','relu')% 激励函数 RELU 
fullyConnectedLayer(numResponses)
regressionLayer];
 
XTrain=XTrain';
YTrain=YTrain';
 
%% 5.定义LSTM函数参数 
def_options();
%% 6.训练LSTM网络 
options = trainingOptions('adam', 'Plots', 'none'); % 设置不显示训练窗口，如果要训练窗口的话就注释掉这行 
net = trainNetwork(XTrain,YTrain,layers,options);
 
%% 7.建立训练模型 
net = predictAndUpdateState(net,XTrain);
 
%% 12.预测未来
[net,YPred(:,1)] = predictAndUpdateState(net,dataPredictStandardized,'ExecutionEnvironment','cpu');%
T_sim = sig*YPred + mu;%预测结果去标准化 ，恢复原来的数量级 
 
end