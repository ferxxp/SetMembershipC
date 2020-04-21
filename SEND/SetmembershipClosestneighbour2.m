function [aprox,time]=SetmembershipClosestneighbour2(S,L,Y,U,NNeighbours)
tic
aproxu=ones(1,length(S)); %#ok<PREALL>
aproxl=ones(1,length(S)); %#ok<PREALL>
[~,sU]=size(U);
[~,sS]=size(S);


index=ones(sS,sU)*inf;

for cont= 1:sU
    index(:,cont,1)=vecnorm((S-U(:,cont)))';
    index(:,cont,2)=Y(cont);
end
for g=1:sS
     index(g,:,:)=sortrows(squeeze(index(g,:,:)));
end
aproxu=min(index(:,1:NNeighbours,1)*L+index(:,1:NNeighbours,2),[],2);
aproxl=max(-index(:,1:NNeighbours,1)*L+index(:,1:NNeighbours,2),[],2);

aprox=(aproxu+aproxl)/2;
time=toc;