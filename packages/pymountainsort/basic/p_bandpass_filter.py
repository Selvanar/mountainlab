import numpy as np

import sys,os
parent_path=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.append(parent_path)

from mlpy import writemda32,readmda,DiskReadMda,DiskWriteMda
from common import TimeseriesChunkReader

import cppimport
cpp=cppimport.imp('bandpass_filter_cpp')

processor_name='pyms.bandpass_filter'
processor_version='0.1'
def bandpass_filter(*,timeseries,timeseries_out,samplerate=30000,freq_min=300,freq_max=6000,freq_wid=1000):
    """
    Normalize the channels in a timeseries array to each have unit variance

    Parameters
    ----------
    timeseries : INPUT
        Path of timeseries, MxN where M is number of channels and N number of timepoints, in .mda format
        
    timeseries_out : OUTPUT
        Path of output timeseries in .mda format
        
    samplerate : double
        (Optional) Sampling rate of input timeseries in Hz
    freq_min : double
        (Optional) Lower edge of freq band
    freq_max : double
        (Optional) Upper edge of freq band
    freq_wid : double
        (Optional) A parameter that controls the sharpness of the band edge transition
        
    """    
    X=DiskReadMda(timeseries)
    M,N = X.N1(),X.N2()    
    _writer=DiskWriteMda(timeseries_out,[M,N],dt=X.dt())
    
    chunk_size_mb=100
    overlap_size=1000
        
    def _kernel(chunk,info):
        print('Processing chunk (%g%%)...' % (np.floor(info.t1/N*100)))
        chunk=chunk.view('float32')
        cpp.bandpass_filter(chunk,samplerate,freq_min,freq_max,freq_wid)        
        return _writer.writeChunk(chunk[:,info.t1a:info.t2a+1],i1=0,i2=info.t1)
    
    TCR=TimeseriesChunkReader(chunk_size_mb=chunk_size_mb, overlap_size=overlap_size)    
    if not TCR.run(timeseries,_kernel):
        return False
    return True

bandpass_filter.name=processor_name
bandpass_filter.version=processor_version  
def test_bandpass_filter():
    M,N = 12,30000
    X=np.random.rand(M,N)
    writemda32(X,'tmp.mda')
    ret=bandpass_filter(timeseries="tmp.mda",timeseries_out="tmp2.mda")
    assert(ret)
    A=readmda('tmp.mda')
    B=readmda('tmp2.mda')
    assert(A.shape==B.shape)
    assert(X.shape==B.shape)
    #np.testing.assert_array_almost_equal(A,B,decimal=6)
    return True 
bandpass_filter.test=test_bandpass_filter

if __name__ == '__main__':
    print ('Running test')
    test_bandpass_filter()