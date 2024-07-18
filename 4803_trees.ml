let read_ii () = Scanf.scanf "%d %d\n" (fun x y -> x, y)
let rec from i j lst = if i > j then lst else from i (j - 1) (j :: lst)
let ( -- ) i j = from i j []

let has_no_cycle (from : int) (graph : int list array) (visited : bool array) : bool =
  let rec has_cycle (cur : int) (parent : int) : bool =
    visited.(cur) <- true;
    List.exists
      (fun nxt -> if visited.(nxt) then nxt <> parent else has_cycle nxt cur)
      graph.(cur)
  in
  not @@ has_cycle from 0
;;

let () =
  let rec test_case (case_no : int) =
    let n, m = read_ii () in
    if n = 0 && m = 0
    then ()
    else (
      Printf.printf "Case %d: " case_no;
      let graph = Array.make (n + 1) [] in
      List.iter
        (fun _ ->
          let a, b = read_ii () in
          graph.(a) <- b :: graph.(a);
          graph.(b) <- a :: graph.(b))
        (1 -- m);
      let visited = Array.make (n + 1) false in
      let num_trees = ref 0 in
      List.iter
        (fun x ->
          if (not visited.(x)) && has_no_cycle x graph visited then incr num_trees)
        (1 -- n);
      (match !num_trees with
       | 0 -> Printf.printf "No trees.\n"
       | 1 -> Printf.printf "There is one tree.\n"
       | k -> Printf.printf "A forest of %d trees.\n" k);
      test_case (case_no + 1))
  in
  test_case 1
;;
