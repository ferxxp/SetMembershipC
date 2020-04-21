function [Lu]=Calcmaxmin(U,Y,error,tasa)
Lu=0;
%Ll=0;
[~,NL]=size(U);
for t=1:NL
    ut=U(:,t);
    for i=t:NL
        ui=U(:,i);
        C=norm(ui-ut);
        while Y(t)>Y(i)+error+C*Lu
            Lu=Lu+tasa;
        end
        %
        %while Y(t)<Y(i)-error+C*Ll
        %    Ll=Ll-tasa;
        %end  
    end
end

