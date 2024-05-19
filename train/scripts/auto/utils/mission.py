import csv
import asyncio
from math import sqrt
from scipy.stats import norm
import numpy as np

# brownian motion FROM https://scipy-cookbook.readthedocs.io/items/BrownianMotion.html
def brownian(x0, n, dt, delta, out=None):
    """
    Generate an instance of Brownian motion (i.e. the Wiener process):

        X(t) = X(0) + N(0, delta**2 * t; 0, t)

    where N(a,b; t0, t1) is a normally distributed random variable with mean a and
    variance b.  The parameters t0 and t1 make explicit the statistical
    independence of N on different time intervals; that is, if [t0, t1) and
    [t2, t3) are disjoint intervals, then N(a, b; t0, t1) and N(a, b; t2, t3)
    are independent.
    
    Written as an iteration scheme,

        X(t + dt) = X(t) + N(0, delta**2 * dt; t, t+dt)


    If `x0` is an array (or array-like), each value in `x0` is treated as
    an initial condition, and the value returned is a numpy array with one
    more dimension than `x0`.

    Arguments
    ---------
    x0 : float or numpy array (or something that can be converted to a numpy array
         using numpy.asarray(x0)).
        The initial condition(s) (i.e. position(s)) of the Brownian motion.
    n : int
        The number of steps to take.
    dt : float
        The time step.
    delta : float
        delta determines the "speed" of the Brownian motion.  The random variable
        of the position at time t, X(t), has a normal distribution whose mean is
        the position at time t=0 and whose variance is delta**2*t.
    out : numpy array or None
        If `out` is not None, it specifies the array in which to put the
        result.  If `out` is None, a new numpy array is created and returned.

    Returns
    -------
    A numpy array of floats with shape `x0.shape + (n,)`.
    
    Note that the initial value `x0` is not included in the returned array.
    """

    x0 = np.asarray(x0)

    # For each element of x0, generate a sample of n numbers from a
    # normal distribution.
    r = norm.rvs(size=x0.shape + (n,), scale=delta*sqrt(dt))

    # If `out` was not given, create an output array.
    if out is None:
        out = np.empty(r.shape)

    # This computes the Brownian motion by forming the cumulative sum of
    # the random samples. 
    np.cumsum(r, axis=-1, out=out)

    # Add the initial condition.
    out += np.expand_dims(x0, axis=-1)

    return out

def reached_checkpoint(setpoint, current_point, epsilon=0.3, mod=0):
    sp = setpoint
    cp = current_point
    if type(sp) is not np.ndarray:
        sp = np.array(sp)
    if type(cp) is not np.ndarray:
        cp = np.array(cp)
    distance = sp-cp
    if mod != 0:
        distance = np.linalg.norm(distance%mod)
    else:
        distance = np.linalg.norm(distance)

    return distance < epsilon, distance

def random_linear_lateral(startingPoint):
    sp = None
    if type(startingPoint) is not np.ndarray:
        sp = np.array(startingPoint)
    # random walk lateral
    rw =  brownian(np.zeros(2), 100, 1, 2)
    rw = np.vstack([rw, np.zeros(rw.shape[1]), np.random.uniform(0, 360, size = rw.shape[1])])
    rw += np.expand_dims(np.array(sp), axis=1) 
    return np.around(np.swapaxes(rw, 0, 1), decimals=2) # output shape: [Timesteps, poisition_dim]

def read_mission_csv_file(file_name):
    nedy = []
    with open(file_name) as f:
        csv_reader = csv.reader(f)
        for row in csv_reader:
            nedy.append([float(r) for r in row])
        pass
    return np.array(nedy)