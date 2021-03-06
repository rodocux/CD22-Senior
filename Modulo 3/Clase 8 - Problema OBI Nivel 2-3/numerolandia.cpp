#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

vi p,r;
vi factor(10000010);


void criba_modificada(){
    factor[0]=1;
    factor[1]=1;
    for(int i=2;i<factor.size();i++) factor[i]=i;
    // CRIBA
    int tam = factor.size();
    for(int i=2;i*i<=tam;i++){
        if(factor[i]==i){ // Es primo
            for(int j=i*i;j<tam;j+=i){
                if(factor[j]==j){ // No ha sido marcado
                    factor[j]=i;
                }
            }
        }
    }
}

void init(int N){
    p.clear();
    r.clear();
    for(int i=0;i<N;i++){
        p.push_back(i);
        r.push_back(1);
    }
}

int buscar(int n){
    if(p[n]==n) return n; // Representante
    return p[n]=buscar(p[n]); // Actualizacion de representante
}

void unir(int a,int b){
    int ra = buscar(a);
    int rb = buscar(b); 
     // Si no estan en el mismo conjunto
    if(ra!=rb){
        // Unir
        if(r[ra]>=r[rb]){
            p[rb]=ra;
            if(r[ra]==r[rb]) r[ra]++;
        }
        else{
            p[ra]=rb;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    criba_modificada();
    vi numeros;
    bool hay_uno = 0;
    int N,x;
    cin>>N;
    init(10000010);
    while(N--){
        cin>>x;
        numeros.push_back(x);
        if(x==1) hay_uno = 1;
        else{
            // Hacemos las conexiones
            int cx = x;
            while(cx>1){
                unir(x,factor[cx]);
                cx = cx / factor[cx];
            }
        }
    }
    int Q;
    cin>>Q;
    while(Q--){
        int a,b;
        cin>>a>>b;
        if(hay_uno) cout<<"SI"<<"\n";
        else if(buscar(numeros[a])==buscar(numeros[b])) cout<<"SI"<<"\n";
        else cout<<"NO"<<"\n";
    }
    return 0;
}