import torch as th
import time

def runme():
  start = time.time()
  x = th.ones(3000, 3000)
  result = (x*x).mean().item()
  duration = (time.time() - start)*1000
  print("  .In Python> operation took {} ms, result {}".format(duration, result))
  print("  .In Python> ok")
  return result
