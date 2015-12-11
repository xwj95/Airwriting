import theano
import theano.tensor as T
import numpy as np
import time
from theano.tensor.nnet.conv import conv2d
from theano.tensor.signal.downsample import max_pool_2d

def floatX(X):
	return np.asarray(X, dtype = theano.config.floatX)

def init_weights(shape):
	return theano.shared(floatX(np.random.randn(*shape) * 0.1), borrow = True)

def init_bias(length):
	return theano.shared(floatX(np.zeros(length)), borrow = True)

def sgd(cost, params, learning_rate):
	grads = T.grad(cost = cost, wrt = params)
	updates = []
	for p, g in zip(params, grads):
		updates.append([p, p - g * learning_rate])
	return updates

def relu(X):
	return T.maximum(X, 0.)

def softmax(X):
	e_x = T.exp(X - X.max(axis = 1).dimshuffle(0, 'x'))
	return e_x / e_x.sum(axis = 1).dimshuffle(0, 'x')

def model(X, w1, w2, w, b):
	l1 = relu(conv2d(X, w1, border_mode = 'full'))
	l1 = max_pool_2d(l1, (2, 2))

	l2 = relu(conv2d(l1, w2))
	l2 = max_pool_2d(l2, (2, 2))
	l2 = T.flatten(l2, outdim = 2)

	l3 = T.dot(l2, w) + b
	l = softmax(l3)
	return l;

def cnn(train_x, train_y, learning_rate = 0.05, batch = 100, epochs = 500):

	train_x = train_x.reshape(-1, 1, 28, 28)

	X = T.dtensor4()
	Y = T.fmatrix()

	w1 = init_weights((8, 1, 3, 3));
	w2 = init_weights((4, 8, 3, 3));
	w = init_weights((196, 62));
	b = init_bias(62);

	l = model(X, w1, w2, w, b)
	y_pred = T.argmax(l, axis = 1)

	cost = T.mean(T.nnet.categorical_crossentropy(l, Y))
	params = [w1, w2, w, b]
	update = sgd(cost, params, learning_rate)

	train = theano.function(inputs = [X, Y], outputs = cost, updates = update, allow_input_downcast = True)
	predict = theano.function(inputs = [X], outputs = y_pred, allow_input_downcast = True)

	now = time.strftime('%X', time.localtime())
	print '[%s] Start training' %(now)
	for epoch in range(epochs):
		hit = 0.0
		for start, end in zip(range(0, train_x.shape[0], batch), range(batch, train_x.shape[0], batch)):
			cost = train(train_x[start:end, :], train_y[start:end, :])
			hit = hit + np.sum(np.argmax(train_y[start:end, :], axis = 1) == predict(train_x[start:end, :]))
		accuracy = hit / train_x.shape[0]
		now = time.strftime('%X', time.localtime())
		print '[%s] epoch %d, accuracy = %.4f' %(now, epoch + 1, accuracy)

	f = open("model.txt", "w")
	lists1 = w1.get_value(borrow = True)
	for i in lists1:
		for j in i:
			for k in j:
				for l in k:
					f.write((str) (l) + "\t")
	f.write("\n")
	lists2 = w2.get_value(borrow = True)
	for i in lists2:
		for j in i:
			for k in j:
				for l in k:
					f.write((str) (l) + "\t")
	f.write("\n")
	lists3 = w.get_value(borrow = True)
	for i in lists3:
		for l in i:
			f.write((str) (l) + "\t")
	f.write("\n")
	lists4 = b.get_value(borrow = True)
	for i in lists4:
		f.write((str) (i) + "\t")
	f.write("\n")
	f.close()
