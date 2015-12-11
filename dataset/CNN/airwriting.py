from load import dataset
from cnn import cnn

train_x, train_y = dataset(onehot = True)
cnn(train_x, train_y)
