import java.util.Scanner

fun main(args: Array<String>) {
    val scan = Scanner(System.`in`)
    val T = scan.nextInt()
    for(_i in 1..T){
        val n = scan.nextInt()
        var a = IntArray(n+1)
        for(i in 1..n){
            val x = scan.nextInt()
            a[i] = x
        }
        var flag = true
        for(i in 2..n){
            if((a[i] - a[i-1]) % 2 == 0) {
                println("YES")
                flag = false
                break
            }
        }
        if(flag)println("NO")
    }
}
