let infty = 0x3f3f3f3f
let read_iii () = Scanf.scanf "%d %d %d\n" (fun x y z -> x, y, z)
let rec from i j lst = if i > j then lst else from i (j - 1) (j :: lst)
let ( -- ) i j = from i j []

let floyd_warshall (adj : int array array) (route : int array array) =
  let n = Array.length adj - 1 in
  List.iter
    (fun via ->
      List.iter
        (fun a ->
          List.iter
            (fun b ->
              if a <> b
              then
                if adj.(a).(b) > adj.(a).(via) + adj.(via).(b)
                then (
                  adj.(a).(b) <- adj.(a).(via) + adj.(via).(b);
                  route.(a).(b) <- via))
            (1 -- n))
        (1 -- n))
    (1 -- n)
;;

let find_route (route : int array array) (a : int) (b : int) : int * int list =
  let rec aux (a : int) (b : int) (path : int list) : int * int list =
    let via = route.(a).(b) in
    if via = 0
    then 2, a :: b :: path
    else (
      let path_via_b_len, path_via_b = aux via b path in
      match path_via_b with
      | [] -> failwith "Unreachable"
      | _ :: path_excl_via_b ->
        let path_a_via_len, path_a_b = aux a via path_excl_via_b in
        path_a_via_len + path_via_b_len - 1, path_a_b)
  in
  aux a b []
;;

let print_route (adj : int array array) (route : int array array) =
  let n = Array.length route - 1 in
  List.iter
    (fun i ->
      List.iter
        (fun j ->
          if adj.(i).(j) = infty
          then Printf.printf "0\n"
          else (
            let path_len, path = find_route route i j in
            Printf.printf "%d " path_len;
            List.iter (fun x -> Printf.printf "%d " x) path;
            Printf.printf "\n"))
        (1 -- n))
    (1 -- n)
;;

let () =
  let n = read_int () in
  let m = read_int () in
  let adj =
    let rec read_lines (num_its : int) (adj : int array array) =
      if num_its > 0
      then (
        let a, b, cost = read_iii () in
        adj.(a).(b) <- Stdlib.min adj.(a).(b) cost;
        read_lines (num_its - 1) adj)
    in
    let mat = Array.make_matrix (n + 1) (n + 1) infty in
    read_lines m mat;
    mat
  in
  let route = Array.make_matrix (n + 1) (n + 1) 0 in
  floyd_warshall adj route;
  List.iter
    (fun i ->
      List.iter
        (fun j -> Printf.printf "%d " @@ if adj.(i).(j) = infty then 0 else adj.(i).(j))
        (1 -- n);
      Printf.printf "\n")
    (1 -- n);
  print_route adj route
;;
