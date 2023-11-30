fn main() {
    println!("Hello Rust!!");
    println!("This will be fizzbuzz kinda for 30 times");

    for i in 1..31 {
        fizzbuzz(i);
    }
}

fn is_divisuble_by(ldsb: u32, rdsb: u32) -> bool {
   if rdsb == 0  { return false; } else { return ldsb % rdsb == 0; }
}

fn fizzbuzz(n: u32) -> () {
   if(is_divisuble_by(n, 15)) {
        println!("fizzbuzz");
   } 
   else if(is_divisuble_by(n, 3)) {
        println!("fizz");
   }
   else if(is_divisuble_by(n, 5)) {
        println!("buzz");
   }
   else {
       println!("{}", n);
   }
}

