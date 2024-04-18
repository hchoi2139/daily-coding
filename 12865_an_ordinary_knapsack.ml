let read_pair () =
  let input = read_line () in
  Scanf.sscanf input "%d %d" (fun x y -> x, y)
;;

let rec read_pairs_aux n acc =
  if n < 1 then acc else read_pairs_aux (n - 1) (read_pair () :: acc)
;;

let read_pairs n () = read_pairs_aux n []

let () =
  let max_capacity, max_weight = read_pair () in
  let weight, value =
    (0, 0) :: read_pairs max_capacity ()
    |> List.split
    |> fun (x, y) -> Array.of_list x, Array.of_list y
  in
  let memo = Array.make_matrix (max_capacity + 1) (max_weight + 1) 0 in
  let res =
    for i = 1 to max_capacity do
      for j = 1 to max_weight do
        if j < weight.(i)
        then memo.(i).(j) <- memo.(i - 1).(j)
        else
          memo.(i).(j) <- max memo.(i - 1).(j) (memo.(i - 1).(j - weight.(i)) + value.(i))
      done
    done;
    memo.(max_capacity).(max_weight)
  in
  print_int res
;;
