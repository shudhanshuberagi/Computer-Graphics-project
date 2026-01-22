#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <iostream.h>
void plotEllipsePoints(int xc,int yc,int x,int y){
    putpixel(xc+x,yc+y,WHITE);
    putpixel(xc-x,yc+y,WHITE);
    putpixel(xc+x,yc-y,WHITE);
    putpixel(xc-x,yc-y,WHITE);
}
void midpointEllipse(int xc,int yc,int a,int b){
    int x=0,y=b;
    long a2=a*a;
    long b2=b*b;
    long dx=2*b2*x;
    long dy=2*a2*y;
    long p2;
    long p1=b2-(a2*b)+(a2/4);
    while(dx<dy){
        plotEllipsePoints(xc,yc,x,y);
        x++;
        dx=dx+(2*b2);
        if(p1<0){
            p1=p1+dx+b2;
        }
        else{
            y--;
            dy=dy-(2*a2);
            p1=p1+dx-dy+b2;
        }
    }
    p2=(b2*(x+0.5)*(x+0.5)+(a2*(y-1)*(y-1))-(a2*b2));
    while(y>0){
        plotEllipsePoints(xc,yc,x,y);
        y--;
        dy=dy-(2*a2);
        if(p2>0){
            p2=p2+a2-dy;
        }
        else{
            x++;
            dx=dx+(2*b2);
            p2=p2+dx-dy+a2;
        }
    }
}
void midpoint_circle_algo(int xc,int yc,int r){
    int x=0,y=r;
    int p=1-r;
    while(x<=y){
        putpixel(xc+x,yc+y,WHITE);
        putpixel(xc-x,yc+y,WHITE);
        putpixel(xc+x,yc-y,WHITE);
        putpixel(xc-x,yc-y,WHITE);
        putpixel(xc+y,yc+x,WHITE);
        putpixel(xc-y,yc+x,WHITE);
        putpixel(xc+y,yc-x,WHITE);
        putpixel(xc-y,yc-x,WHITE);
        if(p<0){
            p+=2*x+1;
        }
        else{
            p+=2*x-2*y+1;
            y--;
        }
        x++;
    }
}
void bresenham_circle_algo(int xc,int yc,int r){
    int x=0,y=r;
    int p=3-2*r;
    while(x<=y){
        putpixel(xc+x,yc+y,WHITE);
        putpixel(xc-x,yc+y,WHITE);
        putpixel(xc+x,yc-y,WHITE);
        putpixel(xc-x,yc-y,WHITE);
        putpixel(xc+y,yc+x,WHITE);
        putpixel(xc-y,yc+x,WHITE);
        putpixel(xc+y,yc-x,WHITE);
        putpixel(xc-y,yc-x,WHITE);
        if(p<0){
            p+=4*x+6;
        }
        else{
            p+=4*(x-y)+10;
            y--;
        }
        x++;
    }
}
void dda_line(int x1,int y1,int x2,int y2){
    int dx,dy,step,xinc,yinc,x,y;
    dx=(x2-x1);
    dy=(y2-y1);
    step=(abs(dx)>=abs(dy))?abs(dx):abs(dy);
    xinc=dx/step;
    yinc=dy/step;
    x=x1;
    y=y1;
    for (int i = 0; i < step; i++)
    {
        putpixel(x,y,WHITE);
        x+=xinc;
        y+=yinc;
    }
}
void bresenham_line(int x1,int y1,int x2,int y2){
    int dx,dy,x,y,p;
    dx=x2-x1;
    dy=y2-y1;
    x=x1;
    y=y1;
    p=2*dy-dx;
    while(x<x2){
        if(p>=0){
            putpixel(x,y,WHITE);
            y=y+1;
            p=p+2*dy-2*dx;
        }
        else{
            putpixel(x,y,WHITE);
            p=p+2*dy;
        }
        x=x+1;
    }
}
void t_s_r_f_e(int x1,int y1,int x,int y,int who){
        int t_s_r;
        cout << "\n--- TRANSFORMATION MENU ---";
        cout << "\n1. Translate";
        cout << "\n2. Scale";
        cout << "\n3. Rotate";
        cout << "\nEnter choice: ";
        cin >> t_s_r;
        if (t_s_r == 1)
        {
            int tx,ty;
            cout<<"Enter tx ty: ";
            cin>>tx>>ty;
            if(who==1)
            midpointEllipse(x1+tx,y1+ty,x,y);
            else if(who==2)
            ellipse(x1+tx,y1+ty,0,360,x,y);
        }
        else if(t_s_r==2){
            float sx, sy;
            cout<<"Enter sx sy: ";
            cin>>sx>>sy;
            if(who==1)
            midpointEllipse(x1*sx,y1*sy,x*sx,y*sy);
            else if(who==2)
            ellipse(x1*sx,y1*sy,0,360,x*sx,y*sy);
        }
        else if(t_s_r==3){
            float angle,rad;
            cout<<"Enter angle (degrees): ";
            cin>>angle;
            rad=angle*3.14/180;
            x1=x1*cos(rad)-y1*sin(rad);
            y1=x1*sin(rad)+y1*cos(rad);
            if(who==1)
            midpointEllipse(x1,y1,x,y);
            else if(who==2)
            ellipse(x1,y1,0,360,x,y);
        }
        else{
            cout<<"\nInvalid choice!";
        }
}
void t_s_r_f(int x1,int y1,int r,int who){
            int t_s_r;
            cout << "\n--- TRANSFORMATION MENU ---";
            cout << "\n1. Translate";
            cout << "\n2. Scale";
            cout << "\nEnter choice: ";
            cin >> t_s_r;
            if(t_s_r==1){
                int tx,ty;
                cout<<"Enter tx ty: ";
                cin>>tx>>ty;
                if (who==1)
                bresenham_circle_algo(x1+tx,y1+ty,r);
                else if(who==2)
                midpoint_circle_algo(x1+tx,y1+ty,r);
                else if(who==3)
                circle(x1+tx,y1+ty,r);
                
            }
            else if(t_s_r==2){
                float s;
                cout<<"Enter s: ";
                cin>>s;
                if (who==1)
                bresenham_circle_algo(x1*s,y1*s,r*s);
                else if(who==2)
                midpoint_circle_algo(x1*s,y1*s,r*s);
                else if(who==3)
                circle(x1*s,y1*s,r*s);
            }
            else{
                cout<<"\nInvalid choice!";
            }
}
void t_s_r_f(int x1,int y1,int x2,int y2,int who){
            int t_s_r;
            cout << "\n--- TRANSFORMATION MENU ---";
            cout << "\n1. Translate";
            cout << "\n2. Scale";
            cout << "\n3. Rotate";
            cout << "\nEnter choice: ";
            cin >> t_s_r;
            if (t_s_r == 1)
            {
                int tx,ty;
                cout<<"Enter tx ty: ";
                cin>>tx>>ty;
                if(who==1)
                dda_line(x1+tx,y1+ty,x2+tx,y2+ty);
                else if(who==2)
                bresenham_line(x1+tx, y1+ty, x2+tx, y2+ty);
                else if(who==3)
                line(x1+tx, y1+ty, x2+tx, y2+ty);
            }
            else if (t_s_r == 2)
            {
                float sx, sy;
                cout<<"Enter sx sy: ";
                cin>>sx>>sy;
                if(who==1)
                dda_line(x1*sx,y1*sy,x2*sx,y2*sy);
                else if(who==2)
                bresenham_line(x1*sx,y1*sy,x2*sx,y2*sy);
                else if(who==3)
                line(x1*sx,y1*sy,x2*sx,y2*sy);
            }
            else if (t_s_r == 3)
            {
                float angle, rad;
                cout<<"Enter angle (degrees): ";
                cin>>angle;
                rad=angle*3.14/180;
                int xr1=x1*cos(rad)-y1*sin(rad);
                int yr1=x1*sin(rad)+y1*cos(rad);
                int xr2=x2*cos(rad)-y2*sin(rad);
                int yr2=x2*sin(rad)+y2*cos(rad);
                if(who==1)
                dda_line(xr1, yr1, xr2, yr2);
                else if(who==2)
                bresenham_line(x1, y1, x2, y2);
                else if(who==3)
                line(x1,y1,x2,y2);
            }
            else{
                cout<<"\nInvalid choice!";
            }
}
void main(){

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    int shape,algo,x1,y1,x2,y2,r;
    cout<<"\n--- MENU ---";
    cout<<"\n1. Line";
    cout<<"\n2. Circle";
    cout<<"\n3. Ellipse";
    cout<<"\n4. Rectangle";
    cout<<"\n5. Triangle";
    cout<<"\nEnter choice: ";
    cin>>shape;
    if(shape==1){
        clrscr();
        cleardevice();
        cout<<"\nLine Algorithm";
        cout<<"\n1. DDA";
        cout<<"\n2. Bresenham";
        cout<<"\n3. Function";
        cout<<"\nEnter choice: ";
        cin>>algo;
        if (algo == 1){
            cout<<"\nEnter x1 y1: ";
            cin>>x1>> y1;
            cout<<"Enter x2 y2: ";
            cin >> x2 >> y2;
            dda_line(x1, y1, x2, y2);
            t_s_r_f(x1,y1,x2,y2,1);
        } 
        else if(algo==2){
            cout<<"\nEnter x1 y1: ";
            cin>>x1>> y1;
            cout<<"Enter x2 y2: ";
            cin >> x2 >> y2;
            bresenham_line(x1, y1, x2, y2);
            t_s_r_f(x1,y1,x2,y2,2);
        }    
        else if(algo==3){
            cout<<"\nEnter x1 y1: ";
            cin>>x1>> y1;
            cout<<"Enter x2 y2: ";
            cin >> x2 >> y2;
            line(x1,y1,x2,y2);
            t_s_r_f(x1,y1,x2,y2,3);
        }        
        else{
            cout<<"\nInvalid choice!";
        }
    }
    else if(shape==2){
        clrscr();
        cleardevice();
        cout<<"\nCircle Drawing Algorithm";
        cout<<"\n1. Bresenham";
        cout<<"\n2. Mid point";
        cout<<"\n3. Function";
        cout<<"\nEnter choice: ";
        cin>>algo;
        if(algo==1){
            cout<<"\nEnter x y: ";
            cin>>x1>>y1;
            cout<<"Enter r: ";
            cin>>r;
            bresenham_circle_algo(x1,y1,r);
            t_s_r_f(x1,y1,r,1);
        }
        else if(algo==2){
            cout<<"\nEnter x y: ";
            cin>>x1>>y1;
            cout<<"Enter r: ";
            cin>>r;
            midpoint_circle_algo(x1,y1,r);
            t_s_r_f(x1,y1,r,2);
        }
        else if(algo==3){
            cout<<"\nEnter x y: ";
            cin>>x1>>y1;
            cout<<"Enter r: ";
            cin>>r;
            circle(x1,y1,r);
            t_s_r_f(x1,y1,r,3);
        }
        else{
            cout<<"\nInvalid choice!";
        }
    }
    else if(shape==3){
        clrscr();
        cleardevice();
        cout<<"\nEllipse Drawing Algorithm";
        cout<<"\n1. Mid point";
        cout<<"\n2. Function";
        cout<<"\nEnter choice: ";
        cin>>algo;
        if(algo==1){

            cout<<"\nEnter center of Ellipse (xc,yc): ";
            cin>>x1>>y1;
            cout << "Enter radius of x and y: ";
            cin>>x2>>y2;
            midpointEllipse(x1,y1,x2,y2);
            t_s_r_f_e(x1,y1,x2,y2,algo);
        }
        else if(algo==2){
            cout<<"\nEnter location of Ellipse x y: ";
            cin>>x1>>y1;
            cout << "Enter radius from x and y: ";
            cin>>x2>>y2;
            ellipse(x1,y1,0,360,x2,y2);
            t_s_r_f_e(x1,y1,x2,y2,algo);
        }
        else{
            cout<<"\nInvalid choice!";
        }
        
    }
    else if(shape==4){
        clrscr();
        cleardevice();
        cout<<"\nRectangle Drawing Algorithm";
        cout<<"\nEnter coordinates of left , top , right , bottom: ";
        cin>>x1>>y1>>x2>>y2;
        rectangle(x1,y1,x2,y2);
        int t_s_r;
        cout << "\n--- TRANSFORMATION MENU ---";
        cout << "\n1. Translate";
        cout << "\n2. Scale";
        cout << "\n3. Rotate";
        cout << "\nEnter choice: ";
        cin >> t_s_r;
        if (t_s_r == 1)
        {
            int tx,ty;
            cout<<"Enter tx ty: ";
            cin>>tx>>ty;
            rectangle(x1+tx,y1+ty,x2+tx,y2+ty);
        }
        else if(t_s_r==2){
            float sx, sy;
            cout<<"Enter sx sy: ";
            cin>>sx>>sy;
            rectangle(x1*sx,y1*sy,x2*sx,y2*sy);
        }
        else if(t_s_r==3){
            float angle,rad;
            cout<<"Enter angle (degrees): ";
            cin>>angle;
            rad=angle*3.14/180;
            x1=x1*cos(rad)-y1*sin(rad);
            y1=x1*sin(rad)+y1*cos(rad);
            x2=x2*cos(rad)-y2*sin(rad);
            y2=x2*sin(rad)+y2*cos(rad);
            rectangle(x1,y1,x2,y2);
        }
        else{
            cout<<"\nInvalid choice!";
        }
    }
    else if(shape==5){
        clrscr();
        cleardevice();
        int tra_1,tra_2;
        cout<<"\nTriangle Drawing Algorithm";
        cout<<"\nEnter coordinates of line 1 X Y: ";
        cin>>x1>>y1;
        cout<<"\nEnter coordinates of line 2 X Y: ";
        cin>>x2>>y2;
        cout<<"\nEnter coordinates of line 3 X Y: ";
        cin>>tra_1>>tra_2;
        line(x1,y1,x2,y2);
        line(x2,y2,tra_1,tra_2);
        line(tra_1,tra_2,x1,y1);
        int t_s_r;
        cout << "\n--- TRANSFORMATION MENU ---";
        cout << "\n1. Translate";
        cout << "\n2. Scale";
        cout << "\n3. Rotate";
        cout << "\nEnter choice: ";
        cin >> t_s_r;
        if (t_s_r == 1)
        {
            int tx,ty;
            cout<<"Enter tx ty: ";
            cin>>tx>>ty;
            line(x1+tx,y1+ty,x2+tx,y2+ty);
            line(x2+tx,y2+ty,tra_1+tx,tra_2+ty);
            line(tra_1+tx,tra_2+ty,x1+tx,y1+ty);
        }
        else if(t_s_r==2){
            float sx, sy;
            cout<<"Enter sx sy: ";
            cin>>sx>>sy;
            line(x1*sx,y1*sy,x2*sx,y2*sy);
            line(x2*sx,y2*sy,tra_1*sx,tra_2*sy);
            line(tra_1*sx,tra_2*sy,x1*sx,y1*sy);
        }
        else if(t_s_r==3){
            float angle,rad;
            cout<<"Enter angle (degrees): ";
            cin>>angle;
            rad=angle*3.14/180;
            x1=x1*cos(rad)-y1*sin(rad);
            y1=x1*sin(rad)+y1*cos(rad);
            x2=x2*cos(rad)-y2*sin(rad);
            y2=x2*sin(rad)+y2*cos(rad);
            tra_1=tra_1*cos(rad)-tra_2*sin(rad);
            tra_2=tra_1*sin(rad)+tra_2*cos(rad);
            line(x1,y1,x2,y2);
            line(x2,y2,tra_1,tra_2);
            line(tra_1,tra_2,x1,y1);
        }
        else{
            cout<<"\nInvalid choice!";
        }
    }
    else{
        cout<<"\nInvalid choice!";
    }
    getch();
    closegraph();
}