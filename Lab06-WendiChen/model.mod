/*********************************************
 * OPL 12.9.0.0 Model
 * Author: 12779
 * Creation Date: 2021年4月4日 at 上午11:27:41
 *********************************************/
{string} Prod = ...;
{string} Process = ...;

int NbMonths = ...;
int ProfitProd[Prod]=...;
float ProcessProd[Process][Prod]= ...;
int MarketProd[1..NbMonths][Prod] = ...;

float CostHold = ...;
int StartHold = ...;
int EndHold = ...;
int MaxHold = ...;

int HoursMonth = ...;

int NumProcess[Process] = ...;
int NumDown[Process] = ...;

dvar int+ make[1..NbMonths][Prod];
dvar int+ store[1..NbMonths][Prod];
dvar int+ sell[1..NbMonths][Prod];
dvar int+ down[1..NbMonths][Process];
dvar float+ SellProfit;
dvar float+ HoldCost;

maximize
	SellProfit - HoldCost;

  
subject to {
	forall (p in Prod){
		forall (r in 1..NbMonths){
			if(r==1){
				make[r][p] == sell[r][p] + store[r][p];
			}
			else{
				store[r-1][p]+make[r][p] == sell[r][p] + store[r][p];			
			}	
		}
	}
	
	forall(p in Prod){
		store[6][p] == EndHold;
	}
	
	forall(p in Prod){
		forall(r in 1..NbMonths){
			store[r][p]<=MaxHold;		
		}	
	}
	
	forall(p in Prod){
		forall(r in 1..NbMonths){
			sell[r][p]<=MarketProd[r][p];		
		}	
	}
	
	forall(c in Process){
		sum(r in 1..NbMonths) (down[r][c]) == NumDown[c];	
	}
	
	forall(c in Process){
		forall(r in 1..NbMonths){
			sum(p in Prod)
			  ProcessProd[c][p]*make[r][p]<=HoursMonth*(NumProcess[c]-down[r][c]);	
		}
	}
	
	SellProfit == sum(p in Prod)sum(r in 1..NbMonths) ProfitProd[p]*sell[r][p];
	HoldCost == sum(p in Prod)sum(r in 1..NbMonths)  CostHold*store[r][p];
	
}


execute {
	if (cplex.getCplexStatus() == 1) {
    	writeln('selling profit = ', SellProfit)
    	writeln('holding cost of y= ', HoldCost)
    	writeln('ret profit = ', SellProfit-HoldCost)
	}
}
