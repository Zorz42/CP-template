// pt: point with integer coordinates (absolute value at most 1e9)
// line{a,b}: infinite line through a!=b, seg{a,b}: segment from a to b (a==b allowed)
// poly: vertices of a simple polygon in order (any orientation), counts as a filled region
// intersect(x,y): whether x and y have a common point, x and y are any of pt, line, seg, poly
// inside(g,p): 0 if p is outside polygon g, 1 if on its boundary, 2 if strictly inside
// side(a,b,c): 1 if a->b->c turns left, -1 if right, 0 if collinear
struct pt{
	ll x,y;
	pt operator-(pt o)const{return{x-o.x,y-o.y};}
	bool operator==(pt o)const{return x==o.x&&y==o.y;}
};
struct line{pt a,b;};
struct seg{pt a,b;};
typedef vc<pt> poly;

ll cross(pt a,pt b){return a.x*b.y-a.y*b.x;}
ll dot(pt a,pt b){return a.x*b.x+a.y*b.y;}
int side(pt a,pt b,pt c){ll v=cross(b-a,c-a);return(v>0)-(v<0);}

bool intersect(pt a,pt b){return a==b;}
bool intersect(pt p,line l){return!side(l.a,l.b,p);}
bool intersect(pt p,seg s){return!side(s.a,s.b,p)&&dot(s.a-p,s.b-p)<=0;}
bool intersect(line l,line m){return cross(l.b-l.a,m.b-m.a)||!side(l.a,l.b,m.a);}
bool intersect(line l,seg s){return side(l.a,l.b,s.a)*side(l.a,l.b,s.b)<=0;}
bool intersect(seg s,seg t){
	if(side(s.a,s.b,t.a)*side(s.a,s.b,t.b)<0&&side(t.a,t.b,s.a)*side(t.a,t.b,s.b)<0)return 1;
	return intersect(t.a,s)||intersect(t.b,s)||intersect(s.a,t)||intersect(s.b,t);
}

int inside(const poly&g,pt p){
	bool in=0;
	rep(i,sz(g)){
		pt a=g[i],b=g[(i+1)%sz(g)];
		if(intersect(p,seg{a,b}))return 1;
		if((a.y>p.y)!=(b.y>p.y)&&(side(a,b,p)>0)==(b.y>a.y))in^=1;
	}
	return 2*in;
}

bool intersect(pt p,const poly&g){return inside(g,p);}
bool intersect(line l,const poly&g){
	int lo=1,hi=-1;
	for(pt p:g)lo=min(lo,side(l.a,l.b,p)),hi=max(hi,side(l.a,l.b,p));
	return lo<=0&&hi>=0;
}
bool intersect(seg s,const poly&g){
	if(inside(g,s.a))return 1;
	rep(i,sz(g))if(intersect(s,seg{g[i],g[(i+1)%sz(g)]}))return 1;
	return 0;
}
bool intersect(const poly&g,const poly&h){
	if(inside(g,h[0])||inside(h,g[0]))return 1;
	rep(i,sz(g))rep(j,sz(h))if(intersect(seg{g[i],g[(i+1)%sz(g)]},seg{h[j],h[(j+1)%sz(h)]}))return 1;
	return 0;
}
template<class A,class B>bool intersect(const A&a,const B&b){return intersect(b,a);}
