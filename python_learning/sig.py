# cross_correlation.py
# Ryan Jensen
# 2018-12-31
"""provides some functions for one-dimensional digital signal processing."""


#===============================================================================
# dependencies
#===============================================================================
import math


#===============================================================================
# methods
#===============================================================================

#-------------------------------------------------------------------------------
def reload():
    """reloads the sig library using importlib.reload()."""
    import sig
    import importlib
    importlib.reload(sig)
    return


#-------------------------------------------------------------------------------
def cross_correlate(sig1, sig2):
    """Calculates the "sliding dot-product" between two input signals. (not normalized)
    
    cross_correlation[n] is the dot product of sig1 and sig2 when sig2[0] is aligned with sig1[n].
    
    This function returns a list containing the cross_correlation signal.
    The total number of elements in the list is (L1 + L2 - 1).
    Maximum index is  len(sig1) - 1
    Minimum index is -len(sig2) + 1
    The last (len(sig2) -1) elements of the cross_correlation list contain the cross correlation results for when n < 0.  For example, the last element of the cross_correlation (cross_corr[-1]) is the result of the dot_product when sig1[0] is aligned with sig2[1] (i.e. sig2 is leading sig1 by a single element)
    This is done purposefully so that cross_correlation signal can be indexed with both positive and negative numbers.  The indexing aligns conveniently with both [python's syntax] and [standard mathematical notation].  This is done for program readability and ease of programming when using the results of cross_correlation.  This should make it less likely for me to introduce bugs into my code via unreadability and confusing organization.
    
    References:
    https://en.wikipedia.org/wiki/Cross-correlation"""
    
    L1 = len(sig1)
    L2 = len(sig2)
    cross_corr = [0] * (L1 + L2 - 1)
    
    # calculate cross correlation for n >= 0
    for n in range(L1):
        print(n)
        cross_corr[n] =         dot_product(sig1[n:], sig2)
    
    # calculate cross correlation for n <  0
    for n in range(1,L2):
        cross_corr[L1+(n-1)] =  dot_product(sig1, sig2[n:])
    
    return (cross_corr,-L2,L1)


#-------------------------------------------------------------------------------
def auto_correlate(sig):
    return cross_correlate(sig,sig)


#-------------------------------------------------------------------------------
def rms(sig):
    """Calculate the root mean square of the signal.
    
    If your signal is thought of as a time-varying amplitude, this function returns the constant amplitude, A, that would produce a power, P, equal to the average power of your signal."""
    return math.sqrt(average_power(sig))


#-------------------------------------------------------------------------------
def average_power(sig):
    """Calculate the mean square of the signal.
    
    If your signal is thought of as a time-varying amplitude, this function returns that signal's average power: sum of energy divided by # of samples."""
    return dot_product(sig,sig)/len(sig)


#-------------------------------------------------------------------------------
def energy(sig):
    """Calculate the total energy of a signal.
    
    If your signal is thought of as a time-varying amplitude, this function returns that signal's total enegry: sum(energy) divided by time (samples).  Units would be enegry/sample"""
    return dot_product(sig,sig)


#-------------------------------------------------------------------------------
def dot_product(list1, list2):
    """Calculates the scalar product of two lists.
    
    If the lists are not equal length: the length over which the dot product is calculated = the length of the shorter of the two vectors."""
    
    L = min(len(list1), len(list2))
    sum = 0
    for i in range(L):
        sum += list1[i] * list2[i]
    
    return sum


#-------------------------------------------------------------------------------