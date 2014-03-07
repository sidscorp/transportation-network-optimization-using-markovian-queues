set supply_node; # farms
set demand_node;  # retail outlets
set hub_node; # granaries
set service_level;

param P{supply_node}; # Supply
param D{demand_node}; # Demand
param dist_ik{supply_node,hub_node};
param dist_jk{demand_node, hub_node};
param service{hub_node, service_level}; 
param u{service_level};
param tr_cost; #Tranport Cost
param u_cost{service_level} ; #Service Level Cost
param op_cost; #Operator Cost

var w{supply_node,hub_node} binary; #Z[i,k]
var x{demand_node, hub_node} binary; #Z[j,k]
var y{hub_node, service_level} binary; #Y[k,l]

minimize cost :
	sum{i in supply_node, k in hub_node} (w[i,k]*P[i]*tr_cost*dist_ik[i,k])+sum{j in demand_node, k in hub_node} (x[j,k]*D[j]*tr_cost*dist_jk[j,k])+ sum{k in hub_node, l in service_level} ((u_cost[l]+op_cost)*y[k,l]);

subject to supply {i in supply_node}:
	sum{k in hub_node} w[i,k] = 1;

subject to demand {j in demand_node}:
	sum{k in hub_node} x[j,k] = 1;

subject to servicelevel_constraint {k in hub_node}:
	sum{l in service_level} y[k,l] = 1;

subject to stagnation {k in hub_node}:
	sum{j in demand_node} D[j]*x[j,k] <= sum{i in supply_node} P[i]*w[i,k];

subject to stagnation_service {k in hub_node}:
	sum{l in service_level} y[k,l]*u[l] >= sum{i in supply_node} w[i,k]*P[i];

subject to time {i in supply_node, j in demand_node, k in hub_node}:
	(((w[i,k]*dist_ik[i,k])+(x[j,k]*dist_jk[j,k]))/60)+ (1/((sum{l in service_level} y[k,l]*u[l]) - (sum{b in supply_node}w[b,k]*P[b]))) <= 240;
