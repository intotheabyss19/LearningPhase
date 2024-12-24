from scipy.optimize import linprog

# Coefficients for the objective function (maximize profit)
# We need to minimize loss, so we take the negative of the profit coefficients
c = [-2, -3]  # Coefficients for M1 and M2

# Coefficients for the inequality constraints
A = [
    [1, 1],
    [2, 1],
]

# Right-hand side of the inequality constraints
b = [400, 600]

# Bounds for x and y (non-negativity constraints)
x_bounds = (0, None)  # x >= 0
y_bounds = (0, None)  # y >= 0

# Solve the linear programming problem
result = linprog(c, A_ub=A, b_ub=b, bounds=[x_bounds, y_bounds], method='highs')

# Output the results
if result.success:
    x, y = result.x
    max_profit = -result.fun  # Negate to get the original profit
    print(f"Optimal number of M1 models to produce: {x:.2f}")
    print(f"Optimal number of M2 models to produce: {y:.2f}")
    print(f"Maximum profit: Rs. {max_profit:.2f}")
else:
    print("Optimization failed.")
