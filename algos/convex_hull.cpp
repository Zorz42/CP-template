// convex_hull(a,include_collinear): replaces a with its convex hull in counter-clockwise order, starting at the smallest point
// include_collinear: also keep points lying on hull edges
// cross(a,b,c): >0 if a->b->c turns left, <0 if right, 0 if collinear
struct pt{
	ll x,y;
	bool operator<(pt o)const{return pll(x,y)<pll(o.x,o.y);}
	bool operator==(pt o)const{return x==o.x&&y==o.y;}
};
ll cross(pt a,pt b,pt c){return(b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);}

void convex_hull(vc<pt>&a,bool include_collinear=0){
	sort(all(a));a.erase(unique(all(a)),a.end());
	if(sz(a)<3)return;
	vc<pt>h;
	rep(it,2){
		int s=sz(h);
		for(pt p:a){
			while(sz(h)>=s+2&&cross(h[sz(h)-2],h.back(),p)<!include_collinear)h.pop_back();
			h.pb(p);
		}
		h.pop_back();reverse(all(a));
	}
	if(sz(h)>sz(a))h.resize(sz(a));
	a=h;
}
