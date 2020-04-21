function [aprox,time]=Setmembershiplocal(S,L,Y,U)
tic
[~,sU]=size(U);
[~,sS]=size(S);
aproxu=ones(1,sS)*Inf;
aproxl=ones(1,sS)*-Inf;

for i=1:sU
    for t=1:sS
        Delta=norm(S(:,t)-U(:,i));
        au=Y(i)+L*Delta;
        al=Y(i)-L*Delta;
        if(aproxu(t)>au)
            aproxu(t)=au;
        end
        if(aproxl(t)<al)
            aproxl(t)=al;
        end
    end
    toc;
end

aprox=(aproxu+aproxl)/2;
time=toc;