#include <bits/stdc++.h>
using namespace std;

#define dt 0.0001
#define gravity make_pair(0.0, -9.7829)
#define boundary make_pair(10.0, 100.0)
#define CoE 0.5
float time_ = 0;

float min(float a, float b){
    return (a > b) ? b : a;
}


class particle{
protected:
    float mass;
    float radius = 0.1;
    pair<float, float> acceleration;
    pair<float, float> velocity;
    pair<float, float> position;
    pair<float, float> prev_position;

    float distance(particle B){
        float dist = (position.first - B.position.first)*(position.first - B.position.first) + (position.second - B.position.second)*(position.second - B.position.second);
        return sqrt(dist);
    }

    void move(){
        acceleration = gravity;

        prev_position = position;

        velocity.first += acceleration.first*dt;
        velocity.second += acceleration.second*dt;

        position.first += velocity.first*dt;
        position.second += velocity.second*dt;
        collide_boundary();
    }
    void collide_boundary(){
        if(position.first < 0 || position.first > boundary.first){
            double gap = abs(min(prev_position.first,  boundary.first - prev_position.first));
            double delta = ((abs(velocity.first) * dt) - gap) * CoE;
            if(position.first < 0){
                position.first = delta;
            }else{
                position.first = (boundary.first - delta);
            }
            velocity.first = -1 * CoE * velocity.first; 
        }
        if(position.second < 0 || position.second > boundary.second){
            float gap = abs(min(prev_position.second,  boundary.second - prev_position.second));
            float delta = ((abs(velocity.second) * dt) - gap) * CoE;
            if(position.second < 0){
                position.second = delta;
            }else{
                position.second = (boundary.second - delta);
            }
            velocity.second = -1 * CoE * velocity.second; 
        }
    }
    void collide_particle(particle &B){
        cout << "collided" <<endl;
        pair<float, float> prev_velocity = velocity;
        velocity.first = ((velocity.first*(1 - CoE) + B.velocity.first*(1 + CoE))) / 2;
        velocity.second = ((velocity.second*(1 - CoE) + B.velocity.second*(1 + CoE))) / 2;

        B.velocity.first = ((prev_velocity.first*(1 + CoE) + B.velocity.first*(1 - CoE))) / 2;
        B.velocity.second = ((prev_velocity.second*(1 + CoE) + B.velocity.second*(1 - CoE))) / 2;
    }

    particle(pair<float, float> p){
        position = p;
    }
    particle(pair<float, float> p, pair<float, float> v){
        position = p;
        velocity = v;
    }
    particle(){
        velocity = make_pair(0.0,  0.0);
        position = make_pair(5.0, 5.0);
    }

    friend class simulation;
};

class simulation{
    vector<particle> particles;
public:
    void generate_particles(int n){
        for(int i = 0; i < n; i++){
            particle A(make_pair(5, i+4));
            particles.push_back(A);
        }
    }
    void simulate(){
        vector<particle>::iterator it = particles.begin();
        vector<particle>::iterator it_ = particles.begin();
        while(it != particles.end()){
            it -> move();
            it_++;
            while(it_ != particles.end()){
                if(it -> distance(*it_) <= 2*it->radius){
                    it -> collide_particle(*it_);   
                }
                it_++;
            }
            it++;
            it_ = it;
        }
        time_ += dt;
    }
    void print_position(){
        cout << time_ <<" ";
        for(auto p: particles){
            cout << p.position.first <<" "<<p.position.second <<" ";
        }
        cout << endl;
    }
    void play(){
        while(1){
            simulate();
            print_position();
        }
    }
};

int main(){
    simulation A;
    A.generate_particles(2);
    A.play();
}