let () =
  let num_meetings = read_int () in
  let meetings =
    let rec read_list n acc =
      if n = 0
      then acc
      else (
        let start_end_pair = Scanf.sscanf (read_line ()) "%d %d" (fun x y -> x, y) in
        read_list (n - 1) (start_end_pair :: acc))
    in
    let cmp a b =
      if snd a = snd b then compare (fst a) (fst b) else compare (snd a) (snd b)
    in
    read_list num_meetings [] |> List.fast_sort cmp
  in
  let res =
    let rec greedy_slide lst prev_end cnt =
      match lst with
      | [] -> cnt
      | (cur_start, cur_end) :: t ->
        if cur_start < prev_end
        then greedy_slide t prev_end cnt
        else greedy_slide t cur_end (cnt + 1)
    in
    greedy_slide meetings Int.min_int 0
  in
  Printf.printf "%d" res
;;
