from django.shortcuts import render, HttpResponse, get_object_or_404, HttpResponseRedirect, redirect, Http404
from .models import Post, Category
from .forms import PostForm, CommentForm
from django.contrib import messages
from django.utils.text import slugify
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.db.models import Q
from django.core.mail import send_mail
from django.conf import settings

def post_index(request):
    post_list = Post.objects.all()
    query = request.GET.get('q')
    category = request.GET.get('kategori')
    mycategory = Category.objects.all().first()
    post_by_category_list = post_list.filter(category__id=mycategory.id)[:3]


    if query:
        post_list = post_list.filter(
            Q(title__icontains=query) | Q(title__icontains=query.replace('i', 'İ')) | Q(title__icontains=query.replace('ı', 'I')) |
            Q(content__icontains=query) |
            Q(user__first_name__icontains=query) |
            Q(user__last_name__icontains=query)
        ).distinct()
    elif category:
        post_list = post_list.filter(category__slug__icontains=category)


    paginator = Paginator(post_list, 5)  # Show 5 posts per page.

    page_number = request.GET.get('sayfa')
    try:
        posts = paginator.get_page(page_number)
    except PageNotAnInteger:
        # If page is not an integer, deliver first page.
        posts = paginator.get_page(1)
    except EmptyPage:
        # If page is out of range (e.g. 9999), deliver last page of results.
        posts = paginator.get_page(paginator.num_pages)

    return render(request, 'post/index.html', {'posts': posts, 'mycategory': mycategory, 'post_by_category': post_by_category_list})


def category_view(request):
    category_list = Category.objects.all()

    return render(request, 'post/category.html', {'category_list': category_list})

def post_detail(request, slug):
    post = get_object_or_404(Post, slug=slug)
    getcategory = Post.objects.filter(category=post.category)[:3]

    form = CommentForm(request.POST or None)
    if form.is_valid():
        comment = form.save(commit=False)
        comment.post = post
        comment.author = request.user
        comment.save()
        messages.success(request, 'Yorumunuz yönetici tarafından onaylandıktan sonra yayınlanacaktır.', extra_tags='yorum-basarili')
        return HttpResponseRedirect(post.get_absolute_url())

    context = {
        'post': post,
        'form': form,
        'post_in_category': getcategory,
    }
    return render(request, 'post/detail.html', context)

def post_create(request):
    if not request.user.is_authenticated:
        return Http404()

    if request.user.is_authenticated:
        if not request.user.is_staff:
            return Http404()

    form = PostForm(request.POST or None, request.FILES or None)
    if form.is_valid():
        post = form.save(commit=False)
        post.user = request.user
        post.save()
        messages.success(request, 'Başarılı bir şekilde oluşturdunuz.', extra_tags='mesaj-basarili')
        # extra_tags,  css class'ı belirtir, bu mesajın classları: success, mesaj-basarili
        return HttpResponseRedirect(post.get_absolute_url())

    context = {
        'form': form,
    }

    return render(request, 'post/form.html', context)

def post_update(request, slug):
    if not request.user.is_authenticated:
        return Http404()

    post = get_object_or_404(Post, slug=slug)
    form = PostForm(request.POST or None, request.FILES or None, instance=post)
    if form.is_valid():
        if request.user == post.user:
            form.save()
            messages.success(request, 'Başarılı bir şekilde düzenlediniz.')
            return HttpResponseRedirect(post.get_absolute_url())
        else:
            messages.warning(request, 'Size ait olmayan bir gönderiyi düzenleyemezsiniz.')
            return redirect('post:index')
    context = {
        'form': form,
    }
    return render(request, 'post/form.html', context)

def post_delete(request, slug):
    if not request.user.is_authenticated:
        return Http404()

    post = get_object_or_404(Post, slug=slug)
    if request.user == post.user:
        post.delete()
        return redirect('post:index')
    else:
        messages.warning(request, 'Size ait olmayan bir gönderiyi silemezsiniz.')
        return redirect('post:index')
