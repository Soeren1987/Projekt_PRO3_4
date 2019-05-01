close all
data = stepdata5;
t = data.second;
v = data.Volt1;
border1 = 4.5;
border2 = 0.1;
v2 = data.Volt;
b = 0;
stop = 0;
tp = [];
tpt = [];
vpt0 = [];
i = 1;
nyv = [];
while (i <= length(t))
    if (v(i)>border1)
        vn = 5;
    else
        vn = 0;
    end
    nyv = [nyv vn];
    i = i + 1;
end
i = 1;


while (i < length(t))
    if ((nyv(i+1)>border1 & nyv(i)<border2) & b == 0)
        t1 = t(i+1);
        stop = 1;
        b = 1;
    end
    i = i + 1;
    vpt0 = [vpt0 0];
    while (stop ~= 2 & b == 1 & i < length(t))
        if (stop == 1)
            while (stop ~= 2 & i < length(t))
                if (nyv(i+1)>border1 & nyv(i)<border2)
                    t2 = t(i+1);
                    stop = 2;
                end
                i = i + 1;
                vpt0 = [vpt0 0];
            end
        end
        if (stop == 2)
            period = t2-t1;
            tpt = [tpt t2];
            vpt0(i) = nyv(i);
            tp = [tp period];
            t1 = t2;
            stop = 1;
        end
    end
end



% while (i < length(t))
%     if ((v(i+1)>border1 & v(i)<border2) & b == 0)
%         t1 = t(i+1);
%         stop = 1;
%         b = 1;
%     end
%     i = i + 1;
%     vpt0 = [vpt0 0];
%     while (stop ~= 2 & b == 1 & i < length(t))
%         if (stop == 1)
%             while (stop ~= 2 & i < length(t))
%                 if (v(i+1)>border1 & v(i)<border2)
%                     t2 = t(i+1);
%                     stop = 2;
%                 end
%                 i = i + 1;
%                 vpt0 = [vpt0 0];
%             end
%         end
%         if (stop == 2)
%             period = t2-t1;
%             tpt = [tpt t2];
%             vpt0(i) = v(i);
%             tp = [tp period];
%             t1 = t2;
%             stop = 1;
%         end
%     end
% end

tprpm = (1*60)./tp;

%hold on
plot(t,v)
xlim([2.5 2.51])
xlabel('Tid (s)') 
ylabel('Spænding (V)') 

figure
plot(t,nyv)
xlim([2.3 2.5])
xlabel('Tid (s)') 
ylabel('Spænding (V)') 
%plot(t,movmean(nyv,100))
hold on

plot(t,vpt0,'.','color','r')
figure
%plot(t,lowpass(movmean(v,10),10,10000))
hold off
plot(tpt,tprpm)
xlabel('Tid (s)') 
ylabel('RPM') 
figure
plot(tpt,movmean(tprpm,200))
xlabel('Tid (s)') 
ylabel('RPM') 
figure
plot(tpt,movmean(tprpm,10))
xlabel('Tid (s)') 
ylabel('RPM')