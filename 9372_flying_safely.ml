let read_ii () = Scanf.scanf "%d %d\n" (fun x y -> x, y)
let rec from i j lst = if i > j then lst else from i (j - 1) (j :: lst)
let ( -- ) i j = from i j []

let () =
  let num_tests = read_int () in
  let rec run_test_case case_no =
    if case_no < num_tests
    then (
      let n, m = read_ii () in
      Printf.printf "%d\n" (n - 1);
      List.iter
        (fun _ ->
          let _ = read_ii () in
          ())
        (1 -- m);
      run_test_case (case_no + 1))
  in
  run_test_case 0
;;
