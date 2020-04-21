function [aprox,time]=SetmembershipClosestneighbour(S,L,Y,U,NNeighbours)
tic
aproxu=ones(1,length(S)); %#ok<PREALL>
aproxl=ones(1,length(S)); %#ok<PREALL>
[~,sU]=size(U);
[~,sS]=size(S);


index=ones(sS,NNeighbours+1)*inf;

for cont= 1:sU
    index(:,NNeighbours+1,1)=vecnorm((S-U(:,cont)))';
    index(:,NNeighbours+1,2)=Y(cont);
    for g=1:sS
        index(g,:,:)=sortrows(squeeze(index(g,:,:)));
    end
end
aproxu=min(index(:,1:5,1)*L+index(:,1:5,2),[],2);
aproxl=max(-index(:,1:5,1)*L+index(:,1:5,2),[],2);

aprox=(aproxu+aproxl)/2;
time=toc;