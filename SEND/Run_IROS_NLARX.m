% load('matlabData2.mat')
% 
% in=[ids900.VarName2,ids900.VarName3,ids900.VarName4,ids900.VarName5];
% out=ids900.VarName6;

DATASET=readtable('/Users/fernandoquevedovallejo/Desktop/Planificacion/papers/graficas/Iros2020-Identification/SetMembershipData.csv');
start=1;
endd=2000;
in=[DATASET.Var3(1:20000),DATASET.Var5(1:20000),DATASET.Var6(1:20000),DATASET.Var7(1:20000)];
out=DATASET.Var8(1:20000);

%divide in ident and val

[Quant,~]=size(in);
inident=in(1:round(Quant*0.7),:);
outident=out(1:round(Quant*0.7));
inval=in(round(Quant*0.7):Quant,:);
outval=out(round(Quant*0.7):Quant);


dataident=iddata(outident,inident,0.02);
dataval=iddata(outval,inval,0.02);
%   Set up the regresor

na=[3];
nb=[3,5,8,0];
nk=[8,7,3,0];
%%
sys=nlarx(dataident,[na,nb,nk]);
syssim=sim(sys,dataval);
%syssearch=nlarx(dataident,[na,nb,nk],'sigmoidnet','NonlinearRegressors','search');
%getreg(syssearch)



goodnessOfFit(syssim.y,dataval.y,'NRMSE')*100
%% 

figure
hold on
title("Salida")
xlabel("t")
ylabel("Y(t)")
plot(dataval.y,"")
plot(syssim.y,"")

legend("Valor real","NLARX aprox")



figure()
title("error")
hold on
xlabel("t")
ylabel("error (%)")
plot((abs(dataval.y-syssim.y))*100)

legend("Error NLARX")

goodnessOfFit(syssim.y,dataval.y,'NRMSE')*100