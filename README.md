Learning source: [Ray tracing in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) 

### Alias for compilation
```sh
# compiles using g++
alias compile='g++ main.cpp -o main includes/camera/Camera.cpp includes/color/Color.cpp includes/hittable/Hittable.cpp includes/interval/Interval.cpp includes/material/Material.cpp includes/ray/Ray.cpp includes/sphere/Sphere.cpp includes/vec3/Vec3.cpp includes/hittableList/HittableList.cpp -lsfml-graphics -lsfml-window -lsfml-system'
# executes the binary
alias exec='./main > out/image.ppm'
# converts to jpg to view on browser
alias convert='ffmpeg -loglevel quiet -i out/image.ppm out/image.jpg -y'
# opens in browser
alias open='x-www-browser out/image.jpg'
# runs all the above commands together
alias run_all='compile && exec && convert && open'
```
