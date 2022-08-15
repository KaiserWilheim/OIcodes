import java.util.Scanner
fun main(args: Array<String>) {
    val scan = Scanner(System.`in`)
    var T = scan.nextInt()
    for(_i in 1..T){
        var ans = 0
        var n = scan.nextInt()
        var k = scan.nextInt()
        for(i in 1..n){
            var a = scan.nextInt()
            var b = scan.nextInt()
            if(a > k)continue
            ans = max(ans, b - max(a, k) + 1)
        }
        println(ans)
    }
}
fun max(a: Int, b: Int): Int{
    if(a >= b)return a
    else return b
}