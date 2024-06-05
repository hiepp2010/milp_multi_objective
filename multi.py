from docplex.mp.model import Model


milp_model= Model(name = "milp")

#Parameter
delta =None


x=milp_model.binary_var(name='x')
y=milp_model.continuous_var(name='y')
z=milp_model.integer_var(name='z',lb=0)

c1= milp_model.add_constraint(x+2*y+z<=4,ctname="ct1")
c2=milp_model.add_constraint(2*z+y<=5,ctname="ct2")
c3=milp_model.add_constraint(x+y>=1,ctname="ct3")


obj=2*x+y+3*z
milp_model.set_objective('max',obj)

milp_model.print_information()

milp_model.solve()

milp_model.print_solution()