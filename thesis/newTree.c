	/* N will represent the depth, assuming max num children are 3 as we do mod 4
		Max number of nodes in a tree will be (3^N+1)/(3-1) [geometric series]
	*/

	// max_nodes = pow( 3.0,N+1 )/(3.0 - 1);

	// max_nodes = (int)pow(3.0,5.0)/2;

	// printf("%d\n\n",max_nodes);
	// queue = (struct node**)malloc(sizeof(struct node*) * max_nodes );
