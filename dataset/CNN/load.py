import scipy.io as spio
import numpy as np
import h5py

def one_hot(x, n):
	o_h = np.zeros((n, x.size))
	o_h[x - 1, np.arange(x.size)] = 1
	return o_h

def dataset(onehot = True):
	data = spio.loadmat('dataset_random.mat', struct_as_record = True)
	train_x = data['trainX'].astype(float)
	train_y = data['trainY'].astype(int)
	# data = spio.loadmat('mnist.mat', struct_as_record = True)
	# train_x = data['train_x'].astype(float)
	# train_y = data['train_y'].astype(int)
	# data = h5py.File('dataset.mat', 'r')
	# train_x = np.array(data['trainX']).astype(float)
	# train_y = np.array(data['trainY']).astype(int)
	# data.close()

	if onehot:
		train_y = one_hot(train_y, 62)

	train_x = train_x.T
	train_y = train_y.T

	return train_x, train_y
