# a simple deep learning framework for single gpu training and testing

-- TODO --
Learning more about backprop and write code.

-- Content -- 
1. IO
1.1. model and optimizer definition
	-- see alexnet.model
	-- see alexnet.optim

1.2. weight io
	-- save weights as binary files
	weight_representation
	layer-type -> params
	layer-type -> params
	...

2. Network definition
2.1 class Tensor
	data and grad representation
	basic data type if float32 

2.2 class Layer
	each layer contains vector of tensor pointers for input, and another
	vector of tensor pointers for output, using shared_ptr

	basic types:
		input, fc, conv, pooling, activation, softmax, reshape
	extended types:
		batch norm, lrn, pyramid pooling, rpn, yolo...

2.3 class Network
	a set of layers representing structure of the network as a DAG

2.4 class Optimizer
	optimize network
	SGD, MOMENTUM, ADAM
	using weight_decay or not


	


