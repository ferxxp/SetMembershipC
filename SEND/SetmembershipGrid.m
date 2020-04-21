function [res]=SetmembershipGrid(S,Grid,info)
[~,sS]=size(S);
res=zeros(1,sS);
Sdelta=round((S-info{2})/info{3});%%truncar es mejor tiempo
for t=1:sS
    res(t)=Grid(getindex(size(Grid),Sdelta(:,t)'));
end