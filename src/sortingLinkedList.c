ctn *sortLinkedList(ctn *top)
{
		ctn *p, *q, *prev;
		int changed = 1;
		

if( top != NULL && top->nextTree != NULL ) {
	while(changed) 
	{
		changed = 0;
		prev=NULL;
		p = top;
		while( p->nextTree != NULL ) 
		{
			if( p->id > p->nextTree->id ) 
			{
				if(prev)
				{
				   prev->nextTree = switchLinkedListElements( p, p->nextTree );
				}
				else
				{
					top=switchLinkedListElements( p, p->nextTree );
				}
				changed = 1;
			}
			prev=p;
			p=p->nextTree;
		}
	}

return top;
}
ctn *switchLinkedListElements(ctn *l1, ctn *l2)
{
l1->nextTree = l2->nextTree;
l2->nextTree = l1;
return l2;
}
