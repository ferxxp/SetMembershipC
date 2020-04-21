function [Datain,Dataout]=CreateData(in,out,RegresorsIn,RegresorOut)
[Nins,Qins]=size(in);
[~,Qouts]=size(out);
if (Qins==Qouts)
    initTime=max([RegresorsIn(:,1)+RegresorsIn(:,2);RegresorOut(:,1)+RegresorOut(:,2)]);
    Dataout=zeros(1,Qouts-initTime);
    Datain=zeros(3,Qouts-initTime);
    for Timemark=1:Qouts-initTime
      
        Dataout(1,Timemark)=out(1,Timemark+initTime);
        rowwritting=1;
        for Nin=1:Nins
            for Regresor=RegresorsIn(Nin,2):RegresorsIn(Nin,1)+RegresorsIn(Nin,2)-1
                Datain(rowwritting,Timemark)=in(Nin,Timemark+initTime-Regresor);
                rowwritting=rowwritting+1;
           end
        end 
        for Regresor=RegresorOut(1,2):RegresorOut(1,1)+RegresorOut(1,2)-1
                Datain(rowwritting,Timemark)=out(Timemark+initTime-Regresor);
                rowwritting=rowwritting+1;
        end
    end
end