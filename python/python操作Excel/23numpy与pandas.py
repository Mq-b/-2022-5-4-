import numpy as np
import pandas as pd

xx = np.arange(15).reshape(5, 3)
yy = np.arange(1, 16).reshape(5, 3)

print(xx)
print(yy)
xx=pd.DataFrame(xx,columns=['语文','数学','外语'])
yy=pd.DataFrame(yy,columns=['语文','数学','外语'])
print(xx)
print(yy)