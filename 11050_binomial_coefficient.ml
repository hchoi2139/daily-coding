let factorials = [| 1; 1; 2; 6; 24; 120; 720; 5040; 40320; 362880; 3628800 |]
let fact n = factorials.(n)
let binom n k = fact n / (fact k * fact (n - k))
let () = Scanf.scanf "%d %d" (fun n k -> Printf.printf "%d\n" (binom n k))
