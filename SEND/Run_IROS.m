%load('matlabData2.mat')
DATASET=readtable('/Users/fernandoquevedovallejo/Desktop/Planificacion/papers/graficas/Iros2020-Identification/SetMembershipData.csv');
start=1000;
endd=10000;
in=[DATASET.Var3(1:20000),DATASET.Var5(1:20000),DATASET.Var6(1:20000),DATASET.Var7(1:20000)];
out=DATASET.Var8(1:20000);
%   N of ins|  |Delay
RegresorIn=[3,8;
            3,8;
            3,8;
            0,0];
        
RegresorOut=[3,1];

[SIN,SOut]=CreateData(in',out',RegresorIn,RegresorOut);

%%
% Divide data in ident and val


[~,Quant]=size(SIN);
Uident=SIN(:,1:round(Quant*0.7));
yident=SOut(:,1:round(Quant*0.7));
Uval=SIN(:,round(Quant*0.7):Quant);
yval=SOut(:,round(Quant*0.7):Quant);

%create delays
IN=[inident(1:round(Quant*0.7)-8,1), inident(1:round(Quant*0.7)-8,2), inident(1:round(Quant*0.7)-8,3)];
OUT=outident(1+8:round(Quant*0.7));
[a,~]=size(inval);
INVAL=[inval(1:a-8,1),inval(1:a-8,2),inval(1:a-8,3)];
OUTVAL=outval(1+8:a);

%% adapt all and train
X = tonndata(IN,false,false);
T = tonndata(OUT,false,false);

trainFcn = 'trainlm';  % Levenberg-Marquardt backpropagation.

% Create a Nonlinear Autoregressive Network with External Input
inputDelays = 1:3;
feedbackDelays = 1:3;
hiddenLayerSize = 10;
net = narxnet(inputDelays,feedbackDelays,hiddenLayerSize,'open',trainFcn);

[x,xi,ai,t] = preparets(net,X,{},T);

% Setup Division of Data for Training, Validation, Testing
net.divideParam.trainRatio = 90/100;
net.divideParam.valRatio = 5/100;
net.divideParam.testRatio = 5/100;

% Train the Network
[net,tr] = train(net,x,t,xi,ai);

%% 

[L]=Calcmaxmin(Uident,yident,0.05,0.01);

[Ycalcu,T]=Setmembershiplocal(Uval,L,yident,Uident);

[Ycalc3,T]=SetmembershipClosestneighbour2(Uval,L,yident,Uident,1);

%[Grid,infogrid]=calculateGrid(L,yident,Uident,0.005);
%save('CalcGrid.mat','Grid','infogrid')
% load CalcGrid.mat
% Ycalc4=SetmembershipGrid(Uval,Grid,infogrid);

XT = tonndata(INVAL,false,false);
TT = tonndata(OUTVAL,false,false);
[x,xi,ai,t] = preparets(net,XT,{},TT);

YNN = net(x,xi,ai);

%% Plots

figure
hold on
title("Salida")
xlabel("t")
ylabel("Y(t)")
plot(DATASET.Var1(round(Quant*0.7):Quant),yval)
plot(DATASET.Var1(round(Quant*0.7):Quant),Ycalcu)
plot(DATASET.Var1(round(Quant*0.7):Quant),Ycalc3,'--')
plot(DATASET.Var1(round(Quant*0.7)+8:Quant),cell2mat(YNN),'-.')
rectangle('pos', [380,11 3,3],'linewidth',3)

title("Up-Chirp response",'Interpreter','latex','FontSize',24)
xlabel("T(s)",'Interpreter','latex','FontSize',24)
ylabel("Inclination ($^{\circ}$)",'Interpreter','latex','FontSize',24)
legend("Valor real","Set membership","N Closest neighbours","NN",'Interpreter','latex','FontSize',12)
xlim([280 400]);
ylim([0 30]);

axes('Position',[.2 .7 .2 .2])
box on
hold on
plot(DATASET.Var1(round(Quant*0.7):Quant),yval)
plot(DATASET.Var1(round(Quant*0.7):Quant),Ycalcu)
plot(DATASET.Var1(round(Quant*0.7):Quant),Ycalc3,'--')
plot(DATASET.Var1(round(Quant*0.7)+8:Quant),cell2mat(YNN),'-.')
xlim([380 383]);
ylim([11 14]);


fprintf("Set Membership")
goodnessOfFit(Ycalcu',yval','NRMSE')*100
fprintf("N Closest neighbours Set Membership")
goodnessOfFit(Ycalc3,yval','NRMSE')*100
fprintf("Neural Network")
goodnessOfFit(OUTVAL(4:size(OUTVAL)),cell2mat(YNN)','NRMSE')*100

saveas(gcf,'graficas/SMIDENTRESULTS','epsc2')
%goodnessOfFit(Ycalc4',yval','NRMSE')*100