bool isSafe(Node * s, int c){
	ArcNode * arc = s->arc;
	while(arc){
		if(arc->node->color==c) return false;
		arc=arc->next;
	}
	return true;
}

backt(Graph *g, Node *s){
	if(s==nullptr) return true;
	for(int c=1;c<=g->V;++c){
		if(isSafe(s, c)){
		s->color = c;
		if(backt(g, s->next)){return true;}
		s->color = 0;
		}
	}
	return false;
	
}
bool optimalColoring(Graph * g){
return backt(g, s)
}


